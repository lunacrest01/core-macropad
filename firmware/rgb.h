#ifndef RGB_H
#define RGB_H

#include <stdint.h>

class RGBController {
public:
    RGBController(uint8_t pin);
    void begin();
    void setLayerColor(uint8_t layer);         
    void setCharging(bool charging);
    void update();                               
private:
    uint8_t dataPin;
    bool charging;
    uint8_t currentLayer;
    uint32_t layerColors[3];                    
    uint32_t chargingColor;
    void setColor(uint32_t color);
};

#endif