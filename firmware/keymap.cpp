#include "keymap.h"
#include "BleKeyboard.h"   

const KeyDef KEYMAP[NUM_LAYERS][ROW_COUNT * COL_COUNT] = {

    {
        _KM(KEY_LEFT_CTRL, 'z'),     
        _KM(KEY_LEFT_CTRL, 'y'),     
        _KM(KEY_LEFT_CTRL, 's'),    

        _KM(KEY_LEFT_CTRL, 'c'),     
        _KM(KEY_LEFT_CTRL, 'v'),    
        _KM(KEY_LEFT_CTRL, 'x'),     

        _LAYER(1),                   
        _MK(MK_PLAY_PAUSE),          
        _MK(MK_MUTE),               
    },

    {
        _K(KEY_F13),                 
        _K(KEY_F14),                
        _K(KEY_F15),                

        _K(KEY_F16),                 
        _K(KEY_F17),                
        _K(KEY_F18),                 

        _LAYER(0),                   
        _MK(MK_PREV_TRACK),         
        _MK(MK_NEXT_TRACK),          
    },
};

const KeyDef ENC_MAP[NUM_LAYERS][2] = {
    { _MK(MK_VOL_UP),     _MK(MK_VOL_DOWN)    },
    { _MK(MK_NEXT_TRACK), _MK(MK_PREV_TRACK)  },
};
