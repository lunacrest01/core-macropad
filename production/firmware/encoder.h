#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

class Encoder {
public:
    Encoder(uint8_t pinA, uint8_t pinB);
    void begin();
    int8_t getDirection();  
private:
    uint8_t aPin, bPin;
    volatile int8_t direction;
    static void IRAM_ATTR isrHandler(void* arg);
    void handleInterrupt();
};

#endif