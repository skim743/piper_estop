#include <UsbEstop.h>

UsbEstop stopButton;

void setup() {
  stopButton.setup();
  stopButton.beginISR();
  stopButton.beginLedBlinkISR();
}

void loop() {
  noInterrupts();
  if (Serial.available() > 0) {
    Serial.println(stopButton.getPinReading());
  }
  else {
    while (!Serial.available()) {
      Serial.begin(500000); // USB Serial
      delay(1000);
    }
  }
  interrupts();
  delay(10);
}