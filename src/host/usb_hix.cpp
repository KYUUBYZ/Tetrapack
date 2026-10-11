#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "usb_hid.h"
#include "config.h"

enum { RID_KEYBOARD = 1, RID_CONSUMER = 2 };

static const uint8_t reportDesc[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD)),
  TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(RID_CONSUMER))
};

static Adafruit_USBD_HID usbHid;

void hidInit() {
  usbHid.setPollInterval(HID_POLL_MS);
  usbHid.setReportDescriptor(reportDesc, sizeof(reportDesc));
  usbHid.begin();
}

bool hidMounted() { return TinyUSBDevice.mounted(); }

static bool waitReady(uint16_t timeoutMs) {
  uint32_t t0 = millis();
  while (!usbHid.ready()) {
    if (millis() - t0 > timeoutMs) return false;
    yield();
  }
  return true;
}

void hidSetKeys(const uint8_t *keys, uint8_t count) {
  if (!hidMounted()) return;
  uint8_t report[6] = {0};
  for (uint8_t i = 0; i < count && i < 6; i++) report[i] = keys[i];
  if (waitReady(5)) usbHid.keyboardReport(RID_KEYBOARD, 0, report);
}

void hidConsumerTap(uint16_t usage) {
  if (!hidMounted()) return;
  if (waitReady(5)) usbHid.sendReport16(RID_CONSUMER, usage);
  if (waitReady(5)) usbHid.sendReport16(RID_CONSUMER, 0);
}