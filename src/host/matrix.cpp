#include <Arduino.h>
#include "matrix.h"
#include "pins.h"

static bool     State[MATRIX_ROWS][MATRIX_COLS];
static uint32_t lockuntil[MATRIX_ROWS][MATRIX_COLS];

void matrixInit() {
    for(uint8_t c : COL_PINS) pinMode(c, INPUT_PULLUP);
    for(uint8_t r : ROW_PINS) pinMode(r, INPUT);  //high impedance
}

bool matrixScan() {
    bool changed = false;
    uint32_t now = millis();
    for (int r = 0; r < MATRIX_ROWS; r++ ) {
        pinMode(ROW_PINS[r], OUTPUT);
        digitalWrite(ROW_PINS[r], LOW);
        delayMicroseconds(5);
        for (int c = 0; c < MATRIX_COLS; c++){
            bool pressed = (digitalRead(COL_PINS[c]) == LOW);
            //"Fast" Debounce
            if (pressed != State[r][c] && (int32_t)(now - lockuntil[r][c]) >= 0) {
                State[r][c] = pressed;
                lockuntil[r][c] = now + DEBOUNCE_MS;
                changed = true;
            }
        }
        pinMode(ROW_PINS[r], INPUT);
    }
    return changed;
}

bool matrixIsPressed(int r, int c) { return State[r][c]; }