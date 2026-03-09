#pragma once
#include <Arduino.h>

class Debounce {
public:
    explicit Debounce(uint16_t debounceMs = 20)
        : _ms(debounceMs), _stable(false), _lastRaw(false),
          _justPressed(false), _justReleased(false), _lastChangeMs(0) {}
    bool update(bool rawPressed) {
        _justPressed  = false;
        _justReleased = false;

        if (rawPressed != _lastRaw) {
            _lastRaw      = rawPressed;
            _lastChangeMs = millis();
        }

        if ((millis() - _lastChangeMs) >= _ms && rawPressed != _stable) {
            _stable = rawPressed;
            if (_stable) _justPressed  = true;
            else         _justReleased = true;
            return true; 
        }
        return false;
    }

    bool isPressed()    const { return _stable;       }
    bool justPressed()  const { return _justPressed;  }
    bool justReleased() const { return _justReleased; }

    void setDebounceMs(uint16_t ms) { _ms = ms; }

private:
    uint16_t _ms;
    bool     _stable;
    bool     _lastRaw;
    bool     _justPressed;
    bool     _justReleased;
    uint32_t _lastChangeMs;
};
