#include "battery.h"

Battery::Battery(uint8_t adcPin, float dividerRatio,
                 uint16_t fullMv, uint16_t emptyMv)
    : _pin(adcPin), _ratio(dividerRatio),
      _fullMv(fullMv), _emptyMv(emptyMv), _lastReportMs(0) {}

void Battery::begin() {
    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);
    pinMode(_pin, INPUT);
}

uint16_t Battery::_readAveragedMv(uint8_t samples) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += analogReadMilliVolts(_pin);
        delayMicroseconds(500);
    }
    uint16_t pinMv = (uint16_t)(sum / samples);
    return (uint16_t)((float)pinMv * _ratio);
}

uint16_t Battery::getMillivolts() {
    return _readAveragedMv();
}

uint8_t Battery::getPercent() {
    uint16_t mv = _readAveragedMv();
    if (mv >= _fullMv)  return 100;
    if (mv <= _emptyMv) return 0;
    return (uint8_t)(((uint32_t)(mv - _emptyMv) * 100UL)
                     / (uint32_t)(_fullMv - _emptyMv));
}

bool Battery::needsReport(uint32_t intervalMs) {
    if ((millis() - _lastReportMs) >= intervalMs) {
        _lastReportMs = millis();
        return true;
    }
    return false;
}

void Battery::printStats() {
    uint16_t mv  = getMillivolts();
    uint8_t  pct = getPercent();
    Serial.printf("[BAT] %u mV  |  %u%%\n", mv, pct);
}
