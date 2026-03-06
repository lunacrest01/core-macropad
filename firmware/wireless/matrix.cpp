#include "matrix.h"
#include "config.h"
#include <Arduino.h>

MatrixScanner::MatrixScanner() {
    rowPins[0] = ROW1; rowPins[1] = ROW2; rowPins[2] = ROW3;
    colPins[0] = COL1; colPins[1] = COL2; colPins[2] = COL3;
}

void MatrixScanner::begin() {
    for (int r = 0; r < ROWS; r++) {
        pinMode(rowPins[r], OUTPUT);
        digitalWrite(rowPins[r], HIGH); 
    }
    for (int c = 0; c < COLS; c++) {
        pinMode(colPins[c], INPUT_PULLUP); 
    }
    // Initialize state arrays
    memset(keyState, 0, sizeof(keyState));
    memset(rawState, 0, sizeof(rawState));
    memset(lastDebounceTime, 0, sizeof(lastDebounceTime));
}

void MatrixScanner::readCols() {
    for (int c = 0; c < COLS; c++) {
        rawState[currentRow][c] = (digitalRead(colPins[c]) == LOW);
    }
}

void MatrixScanner::scan() {
    static int currentRow = 0;

    for (int r = 0; r < ROWS; r++) {
        digitalWrite(rowPins[r], HIGH);
    }
    digitalWrite(rowPins[currentRow], LOW);
    delayMicroseconds(10); 
    readCols();

    for (int c = 0; c < COLS; c++) {
        if (rawState[currentRow][c] != keyState[currentRow][c]) {
            lastDebounceTime[currentRow][c] = millis();
        }
        if ((millis() - lastDebounceTime[currentRow][c]) > DEBOUNCE_TIME) {
            if (rawState[currentRow][c] != keyState[currentRow][c]) {
                keyState[currentRow][c] = rawState[currentRow][c];
            }
        }
    }
    currentRow = (currentRow + 1) % ROWS;
}

bool MatrixScanner::getKeyPress(uint8_t row, uint8_t col) {
    return keyState[row][col];
}

bool MatrixScanner::anyKeyPressed() {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (keyState[r][c]) return true;
    return false;
}