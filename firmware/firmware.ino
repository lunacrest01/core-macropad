#include <Arduino.h>
#include <FastLED.h>

#include "BleKeyboard.h"
#include "config.h"
#include "keymap.h"
#include "debounce.h"
#include "battery.h"

BleKeyboard bleKeyboard(BLE_DEVICE_NAME, BLE_MANUFACTURER, 100);
Battery     battery(BAT_ADC_PIN, BAT_DIVIDER_RATIO, BAT_FULL_MV, BAT_EMPTY_MV);
CRGB        leds[RGB_LED_COUNT];
Debounce    keyDb[ROW_COUNT * COL_COUNT];  

uint8_t  currentLayer = 0;

volatile int32_t encDelta  = 0;   
volatile uint8_t encState  = 0;   

static const int8_t ENC_TABLE[16] = {
     0, -1,  1,  0,
     1,  0,  0, -1,
    -1,  0,  0,  1,
     0,  1, -1,  0
};

void IRAM_ATTR encoderISR() {
    uint8_t a = (uint8_t)digitalRead(ENC_A_PIN);
    uint8_t b = (uint8_t)digitalRead(ENC_B_PIN);
    encState  = ((encState << 2) | (a << 1) | b) & 0x0F;
    encDelta += ENC_TABLE[encState];
}


static const CRGB LAYER_COLOURS[NUM_LAYERS] = {
    CRGB(0, 80, 220),   
    CRGB(200, 20, 20),  
};

void rgbSetLayer() {
    fill_solid(leds, RGB_LED_COUNT, LAYER_COLOURS[currentLayer]);
    leds[8] = CRGB::Gold;   
    FastLED.show();
}

void rgbFlashKey(uint8_t idx) {
    CRGB saved = leds[idx];
    leds[idx]  = CRGB::White;
    FastLED.show();
    delay(KEY_FLASH_MS);
    leds[idx] = saved;
    FastLED.show();
}

void rgbLowBatWarning() {
    for (uint8_t i = 0; i < 3; i++) {
        fill_solid(leds, RGB_LED_COUNT, CRGB::Red);
        FastLED.show();
        delay(150);
        fill_solid(leds, RGB_LED_COUNT, CRGB::Black);
        FastLED.show();
        delay(100);
    }
    rgbSetLayer();
}

void sendKey(const KeyDef &k) {
    if (!bleKeyboard.isConnected()) return;

    switch (k.type) {
        case KTYPE_REGULAR:
            if (k.modifier) bleKeyboard.press(k.modifier);
            if (k.code)     bleKeyboard.press((uint8_t)k.code);
            delay(BLE_KEY_MS);
            bleKeyboard.releaseAll();
            break;

        case KTYPE_MEDIA: {
            MediaKeyReport mr = { (uint8_t)(k.code & 0xFF),
                                  (uint8_t)((k.code >> 8) & 0xFF) };
            bleKeyboard.write(mr);
            break;
        }

        default:
            break;   
    }
}

void scanMatrix() {
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        digitalWrite(ROW_PINS[r], LOW);
        delayMicroseconds(5);  

        for (uint8_t c = 0; c < COL_COUNT; c++) {
            uint8_t idx    = r * COL_COUNT + c;
            bool    rawLow = (digitalRead(COL_PINS[c]) == LOW);

            if (keyDb[idx].update(rawLow) && keyDb[idx].justPressed()) {
                const KeyDef &k = KEYMAP[currentLayer][idx];

                Serial.printf("[KEY] idx=%u layer=%u type=%u mod=0x%02X code=%u\n",
                              idx, currentLayer, k.type, k.modifier, k.code);

                if (k.type == KTYPE_LAYER) {
                    currentLayer = (uint8_t)k.code;
                    Serial.printf("[LAYER] -> %u\n", currentLayer);
                    rgbSetLayer();
                } else if (k.type != KTYPE_NONE) {
                    sendKey(k);
                    rgbFlashKey(idx);
                }
            }
        }

        
        digitalWrite(ROW_PINS[r], HIGH);
    }
}

void handleEncoder() {
    const int8_t ENC_TICKS_PER_DETENT = 4;

    int32_t delta = 0;
    noInterrupts();
    delta    = encDelta;
    encDelta = 0;
    interrupts();

    int32_t detents = delta / ENC_TICKS_PER_DETENT;

    for (int32_t i = 0; i < detents; i++) {
        Serial.println("[ENC] CW");
        sendKey(ENC_MAP[currentLayer][0]);  
    }
    for (int32_t i = 0; i > detents; i--) {
        Serial.println("[ENC] CCW");
        sendKey(ENC_MAP[currentLayer][1]);   
    }
}

void handleBattery() {
    if (!battery.needsReport(BAT_REPORT_MS)) return;

    battery.printStats();
    uint8_t pct = battery.getPercent();

    if (bleKeyboard.isConnected()) {
        bleKeyboard.setBatteryLevel(pct);
    }

    if (pct <= BAT_LOW_WARN_PCT) {
        rgbLowBatWarning();
    }
}

void rgbIdleAnimate() {
    static uint8_t hue  = 0;
    static uint32_t lastMs = 0;
    if ((millis() - lastMs) < 30) return;
    lastMs = millis();
    fill_rainbow(leds, RGB_LED_COUNT, hue, 255 / RGB_LED_COUNT);
    FastLED.show();
    hue++;
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("=== MacroPad S3 boot ===");

    // Matrix rows
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        pinMode(ROW_PINS[r], OUTPUT);
        digitalWrite(ROW_PINS[r], HIGH);  
    }
    for (uint8_t c = 0; c < COL_COUNT; c++) {
        pinMode(COL_PINS[c], INPUT_PULLUP);
    }

    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
    encState = ((uint8_t)digitalRead(ENC_A_PIN) << 1) | (uint8_t)digitalRead(ENC_B_PIN);
    attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderISR, CHANGE);

    for (uint8_t i = 0; i < ROW_COUNT * COL_COUNT; i++) {
        keyDb[i].setDebounceMs(DEBOUNCE_MS);
    }

  
    FastLED.addLeds<WS2812B, RGB_DATA_PIN, GRB>(leds, RGB_LED_COUNT);
    FastLED.setBrightness(RGB_BRIGHTNESS);
    fill_solid(leds, RGB_LED_COUNT, CRGB::Black);
    FastLED.show();

    battery.begin();
    battery.printStats();

    uint8_t initPct = battery.getPercent();
    bleKeyboard.begin();
    bleKeyboard.setBatteryLevel(initPct);
    Serial.printf("[BLE] Advertising as \"%s\"  (bat=%u%%)\n",
                  BLE_DEVICE_NAME, initPct);
}

void loop() {
    if (bleKeyboard.isConnected()) {
        static bool wasConnected = false;
        if (!wasConnected) {
            wasConnected = true;
            Serial.println("[BLE] Connected!");
            rgbSetLayer();
        }

        scanMatrix();
        handleEncoder();
        handleBattery();

    } else {
        static bool wasConnected = true;
        if (wasConnected) {
            wasConnected = false;
            Serial.println("[BLE] Disconnected - advertising...");
        }
        rgbIdleAnimate();   
        delay(10);
    }
}
