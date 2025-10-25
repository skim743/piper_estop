#include <UsbEstop.h>

IntervalTimer UsbEstop::timerISR;
UsbEstop* UsbEstop::instance = nullptr;
UsbEstop::UsbEstop() {
    instance = this;
    pinReading = 0;
}
IntervalTimer UsbEstop::ledTimer;
volatile bool UsbEstop::ledState = false;

void UsbEstop::setup() {
    pinMode(_pinOut, OUTPUT);
    pinMode(_pinIn, INPUT_PULLDOWN);
    digitalWrite(_pinOut, HIGH); // Output pin is always HIGH

    Serial.begin(500000); // USB Serial
    while (!Serial.available()) {
        delay(1000);
    }
}

void UsbEstop::beginISR() {
    timerISR.begin(isrHandler, 1000000*_ISRperiod); // In us
}

void UsbEstop::isrHandler() {
    // Use the static instance pointer to access member variables
    if (instance) {
        instance->pinReading = digitalRead(_pinIn);
    }
}

bool UsbEstop::getPinReading() {
    int current_reading = pinReading;
    return current_reading;
}

void UsbEstop::beginLedBlinkISR() {
    pinMode(_ledPin, OUTPUT);
    ledState = false;
    digitalWrite(_ledPin, LOW);
    ledTimer.begin(ledBlinkISR, 2000000); // Start with 2 seconds interval
}

void UsbEstop::ledBlinkISR() {
    if (!ledState) {
        // LED is OFF, turn ON for a quick flash
        ledState = true;
        digitalWrite(_ledPin, HIGH);
        ledTimer.begin(ledBlinkISR, 50000); // 50 ms ON
    } else {
        // LED is ON, turn OFF for the rest of the period
        ledState = false;
        digitalWrite(_ledPin, LOW);
        ledTimer.begin(ledBlinkISR, 1950000); // 1950 ms OFF
    }
}