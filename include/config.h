#pragma once
#include <stdint.h>

constexpr int MATRIX_ROWS = 3;
constexpr int MATRIX_COLS = 3;
constexpr uint32_t SCAN_PERIOD_US = 1000;       // scan every ms 
constexpr uint32_t DEBOUNCE_MS = 5;             //key is ignored for 5ms

constexpr int ENC_STEP_PER_DETENT = 4; 
constexpr bool ENC_INVERT = false;              //put true to reverse the direction

constexpr uint8_t HID_POLL_MS = 1;              // 1ms = 1000Hz, this makes the macropad "high pulling"
constexpr uint8_t LED_BRIGHTNESS = 20;

// Keymap
constexpr uint8_t KEYMAP [MATRIX_ROWS][MATRIX_COLS] = {
    {0x1E, 0x1F, 0x20},     // 1 2 3
    {0x21, 0x22, 0x23},      // 4 5 6
    {0x24, 0x25, 0x26},     // 7 8 9
};