#pragma once
#include <stdint.h>

constexpr uint16_t CONSUMER_VOL_UP   = 0x00E9;
constexpr uint16_t CONSUMER_VOL_DOWN = 0x00EA;

void hidInit();
bool hidMounted();
void hidSetKeys(const uint8_t *keys, uint8_t count);   // max 6 keys
void hidConsumerTap(uint16_t usage);