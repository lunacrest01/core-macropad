#pragma once

#define BLE_DEVICE_NAME  "Core-W"
#define BLE_MANUFACTURER "Lunacrest"

#define ROW_COUNT  3
#define COL_COUNT  3
static const uint8_t ROW_PINS[ROW_COUNT] = { 1, 2, 3 };   
static const uint8_t COL_PINS[COL_COUNT] = { 7, 8, 9 };   

#define ENC_A_PIN   10  
#define ENC_B_PIN   12  
#define ENC_SW_ROW  2
#define ENC_SW_COL  2    

#define RGB_DATA_PIN    4    
#define RGB_LED_COUNT   9
#define RGB_BRIGHTNESS  70   

#define BAT_ADC_PIN          6      
#define BAT_DIVIDER_RATIO    2.0f
#define BAT_FULL_MV          4200   
#define BAT_EMPTY_MV         3000   
#define BAT_LOW_WARN_PCT     15     
#define BAT_REPORT_MS        30000UL  

#define DEBOUNCE_MS  20  

#define NUM_LAYERS   2

#define KEY_FLASH_MS  35   
#define BLE_KEY_MS    12   
