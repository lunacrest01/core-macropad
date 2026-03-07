#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

class MatrixScanner {
public:
    MatrixScanner();
    void begin();
    void scan();                      
    bool getKeyPress(uint8_t row, uint8_t col); 
    bool anyKeyPressed();              

private:
    static const uint8_t DEBOUNCE_TIME = 5; 
    uint8_t colPins[COLS];
    bool keyState[ROWS][COLS];         
    bool rawState[ROWS][COLS];          
    uint32_t lastDebounceTime[ROWS][COLS];
    void readCols();
};

#endif