#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "pins.h"
#include "config.h"
#include "matrix.h"
#include "encoder.h"
#include "usb_hid.h"

static Adafruit_NeoPixel led(1, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800);
static uint32_t lastColor = 0xFFFFFFFF;

static void setLed(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color = led.Color(r, g, b);
  if (color == lastColor) return;       
  lastColor = color;
  led.setPixelColor(0, color);
  led.show();
}

static void sendKeys() {
  uint8_t keys[6];
  uint8_t n = 0;
  for (int r = 0; r < MATRIX_ROWS; r++)
    for (int c = 0; c < MATRIX_COLS; c++)
      if (matrixIsPressed(r, c) && n < 6) keys[n++] = KEYMAP[r][c];
  hidSetKeys(keys, n);
}

void setup() {
  led.begin();
  led.setBrightness(LED_BRIGHTNESS);
  setLed(255, 0, 0);          // red: waiting for pc
  matrixInit();
  encoderInit();
  hidInit();
}

void loop() {
  static uint32_t lastScan = 0;
  static uint32_t flashUntil = 0;

  // Encoder
  int dir = encoderPoll();
  if (dir > 0)      hidConsumerTap(CONSUMER_VOL_UP);
  else if (dir < 0) hidConsumerTap(CONSUMER_VOL_DOWN);

  // Matrix: every 1 ms
  uint32_t now = micros();
  if (now - lastScan >= SCAN_PERIOD_US) {
    lastScan = now;
    if (matrixScan()) {
      sendKeys();
      flashUntil = millis() + 60;
    }
  }

  // LED di stato
  if (!hidMounted())            setLed(255, 0, 0);   // red: not connected
  else if (millis() < flashUntil) setLed(0, 255, 0); // green: key
  else                          setLed(0, 0, 40);    // blue: ready
}