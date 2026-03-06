#include "encoder.h"
#include <Arduino.h>

Encoder::Encoder(uint8_t pinA, uint8_t pinB) : aPin(pinA), bPin(pinB), direction(0) {}

void Encoder::begin() {
    pinMode(aPin, INPUT_PULLUP);
    pinMode(bPin, INPUT_PULLUP);
    attachInterruptArg(digitalPinToInterrupt(aPin), isrHandler, this, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(bPin), isrHandler, this, CHANGE);
}

void IRAM_ATTR Encoder::isrHandler(void* arg) {
    Encoder* enc = static_cast<Encoder*>(arg);
    enc->handleInterrupt();
}

void Encoder::handleInterrupt() {
    static uint8_t lastState = 0;
    uint8_t a = digitalRead(aPin);
    uint8_t b = digitalRead(bPin);
    uint8_t state = (a << 1) | b;
    // Gray code transition table
    if (state != lastState) {
        if ((lastState == 0 && state == 1) || (lastState == 1 && state == 3) ||
            (lastState == 3 && state == 2) || (lastState == 2 && state == 0)) {
            direction++;
        } else if ((lastState == 0 && state == 2) || (lastState == 2 && state == 3) ||
                   (lastState == 3 && state == 1) || (lastState == 1 && state == 0)) {
            direction--;
        }
        lastState = state;
    }
}

int8_t Encoder::getDirection() {
    int8_t val;
    noInterrupts();
    val = direction;
    direction = 0;
    interrupts();
    return val;
}