#include <Arduino.h>
#include "config.h"
#include "keymap.h"
#include "matrix.h"
#include "encoder.h"
#include "rgb.h"
#include "battery.h"
#include "blekeyboard.h"

// Global objects
MatrixScanner matrix;
Encoder encoder(ENC_A, ENC_B);
RGBController rgb(RGB_DATA_PIN);
BatteryMonitor battery(BATTERY_PIN, CHARGING_PIN);
BLEKeyboard bleKeyboard;

// Variables
uint8_t currentLayer = 0;
uint32_t lastMatrixScan = 0;
uint32_t lastKeySend = 0;
const uint16_t MATRIX_SCAN_INTERVAL = 5;   
const uint16_t KEY_REPORT_INTERVAL = 10;   

void setup() {
    Serial.begin(115200);
    matrix.begin();
    encoder.begin();
    rgb.begin();
    battery.begin();
    bleKeyboard.begin();

    rgb.setLayerColor(currentLayer);
}

void loop() {
    uint32_t now = millis();


    if (now - lastMatrixScan >= MATRIX_SCAN_INTERVAL) {
        matrix.scan();
        lastMatrixScan = now;
    }


    int8_t encDir = encoder.getDirection();
    if (encDir != 0) {
        uint8_t keycode = (encDir > 0) ? encoder_actions[currentLayer].clockwise : encoder_actions[currentLayer].counterClockwise;
        uint8_t report[1] = { keycode };
        bleKeyboard.sendKeys(0, report, 1);
        delay(KEY_REPORT_INTERVAL);
        bleKeyboard.sendKeys(0, NULL, 0);
    }

    uint8_t pressedKeys[6];
    uint8_t pressedCount = 0;
    uint8_t modifiers = 0; 

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (matrix.getKeyPress(r, c)) {
                uint8_t keycode = keymaps[currentLayer][r][c];
                if (keycode != 0) {
                    pressedKeys[pressedCount++] = keycode;
                    if (pressedCount >= 6) break;
                }
            }
        }
    }

    if (pressedCount > 0 && (now - lastKeySend >= KEY_REPORT_INTERVAL)) {
        bleKeyboard.sendKeys(modifiers, pressedKeys, pressedCount);
        lastKeySend = now;
    } else if (pressedCount == 0 && (now - lastKeySend >= KEY_REPORT_INTERVAL)) {
        bleKeyboard.sendKeys(modifiers, NULL, 0);
        lastKeySend = now;
    }.
    static bool layerSwitchPending = false;
    if (matrix.getKeyPress(0, 2)) { 
        if (!layerSwitchPending) {
            layerSwitchPending = true;
            currentLayer = (currentLayer + 1) % LAYERS;
            rgb.setLayerColor(currentLayer);
        }
    } else {
        layerSwitchPending = false;
    }

    battery.update();
    uint8_t battPercent = battery.getPercentage();
    bleKeyboard.setBatteryLevel(battPercent);
    rgb.setCharging(battery.isCharging());

    bleKeyboard.update();

    delay(1);
}