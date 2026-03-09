#pragma once
#include <Arduino.h>
#include "config.h"


#define KTYPE_NONE     0   
#define KTYPE_REGULAR  1   
#define KTYPE_MEDIA    2   
#define KTYPE_LAYER    3  


#define MK_NEXT_TRACK   1    
#define MK_PREV_TRACK   2    
#define MK_STOP         4    
#define MK_PLAY_PAUSE   8    
#define MK_MUTE         16   
#define MK_VOL_UP       32   
#define MK_VOL_DOWN     64   

typedef struct {
    uint8_t  type;      
    uint8_t  modifier;  
    uint16_t code;      
} KeyDef;

extern const KeyDef KEYMAP[NUM_LAYERS][ROW_COUNT * COL_COUNT];
extern const KeyDef ENC_MAP[NUM_LAYERS][2];

#define _K(code)           { KTYPE_REGULAR, 0,        (uint16_t)(code)  }
#define _KM(mod, code)     { KTYPE_REGULAR, (uint8_t)(mod), (uint16_t)(code) }
#define _MK(mk)            { KTYPE_MEDIA,   0,        (uint16_t)(mk)    }
#define _LAYER(n)          { KTYPE_LAYER,   0,        (uint16_t)(n)     }
#define _NONE              { KTYPE_NONE,    0,        0                 }
