#include <Arduino.h>

class Battery {
public:
    Battery(uint8_t  adcPin,
            float    dividerRatio = 2.0f,
            uint16_t fullMv       = 4200,
            uint16_t emptyMv      = 3000);

    void begin();
    uint8_t  getPercent();
    uint16_t getMillivolts();
    bool needsReport(uint32_t intervalMs);
    void printStats();

private:
    uint8_t  _pin;
    float    _ratio;
    uint16_t _fullMv;
    uint16_t _emptyMv;
    uint32_t _lastReportMs;

    uint16_t _readAveragedMv(uint8_t samples = 8);
};
