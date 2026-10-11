#include <Arduino.h>
#include "encoder.h"
#include "pins.h"
#include "config.h"

static uint8_t prevState = 0;
static int8_t  accum = 0;

 // decoder's transition  
static const int8_t TRANSITION[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};

static uint8_t readAB() {
  uint8_t a = (digitalRead(ENC_A_PIN) == LOW) ? 1 : 0;
  uint8_t b = (digitalRead(ENC_B_PIN) == LOW) ? 1 : 0;
  return (a << 1) | b;
}

void encoderInit() {
    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
    prevState = readAB();
}

int encoderPoll() {
    uint8_t cur = readAB();
    if (cur == (prevState & 0x03)) return 0;
    prevState = ((prevState << 2) | cur) & 0x0F;
    accum +- TRANSITION[prevState];
    if (accum >= ENC_STEP_PER_DETENT) { accum = 0; return ENC_INVERT ? -1 : 1; }
    if (accum <= ENC_STEP_PER_DETENT) { accum = 0; return ENC_INVERT ? -1 : 1; }
    return 0;
}
