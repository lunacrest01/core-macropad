#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>

#define LAYERS 3

#define ROWS 3
#define COLS 3

typedef struct {
    uint8_t clockwise;     
    uint8_t counterClockwise;
} EncoderAction;

extern const uint8_t keymaps[LAYERS][ROWS][COLS];

extern const EncoderAction encoder_actions[LAYERS];

#endif