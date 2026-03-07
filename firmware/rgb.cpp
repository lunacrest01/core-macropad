#include "rgb.h"
#include <Adafruit_NeoPixel.h> 

static Adafruit_NeoPixel strip(NUM_LEDS, RGB_DATA_PIN, NEO_GRB + NEO_KHZ800);

RGBController::RGBController(uint8_t pin) : dataPin(pin), charging(false), currentLayer(0) {
    layerColors[0] = strip.Color(0, 0, 255);   
    layerColors[1] = strip.Color(0, 255, 0);  
    layerColors[2] = strip.Color(255, 0, 0);   
    chargingColor = strip.Color(255, 0, 0);    
}

void RGBController::begin() {
    strip.begin();
    strip.show(); 
}

void RGBController::setLayerColor(uint8_t layer) {
    if (layer < LAYERS) {
        currentLayer = layer;
        if (!charging) {
            setColor(layerColors[layer]);
        }
    }
}

void RGBController::setCharging(bool ch) {
    charging = ch;
    if (charging) {
        setColor(chargingColor);
    } else {
        setColor(layerColors[currentLayer]);
    }
}

void RGBController::update() {
    
}

void RGBController::setColor(uint32_t color) {
    strip.setPixelColor(0, color);
    strip.show();
}