#ifndef USB_ESTOP_H
#define USB_ESTOP_H

#include <Arduino.h>

class UsbEstop {
    public:
        UsbEstop();
        void setup();
        void beginISR();
        static void isrHandler();
        bool getPinReading();

        void beginLedBlinkISR();
        static void ledBlinkISR();

    private:
        static constexpr int _pinIn = 19;
        static constexpr int _pinOut = 6;
        static constexpr int _ledPin = 13;

        static constexpr float _ISRperiod = 0.01; // 10 ms
        static IntervalTimer timerISR;
        static IntervalTimer ledTimer;
        volatile int pinReading;
        static UsbEstop* instance;
        static volatile bool ledState;
};
#endif