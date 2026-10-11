#pragma once
#include <stdint.h>

//3x3 Matrix (Switches)
constexpr uint8_t COL_PINS[3] = {0, 1, 2};
constexpr uint8_t ROW_PINS[3] = {3, 4, 5};

//Encoder
constexpr uint8_t ENC_A_PIN = 10;
constexpr uint8_t ENC_B_PIN = 11;

//I2C1 (Oled)
constexpr uint8_t I2C_SDA_PIN = 26;
constexpr uint8_t I2C_SCL_PIN = 27;

//RP2040-ZERO's LED
constexpr uint8_t STATUS_LED_PIN = 16;