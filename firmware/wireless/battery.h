#ifndef BATTERY_H
#define BATTERY_H

#include <stdint.h>

class BatteryMonitor {
public:
    BatteryMonitor(uint8_t adcPin, uint8_t chgPin);
    void begin();
    void update();                    
    uint8_t getPercentage();          
    bool isCharging();
private:
    uint8_t adcPin, chgPin;
    uint8_t percentage;
    bool charging;
    uint32_t lastRead;
    void readVoltage();
};

#endif