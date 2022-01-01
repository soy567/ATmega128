#include "led.h"

void offAllLed() {
    LED_PORT &= ~((1 << LED1) | (1 << LED2) | (1 << LED3));
}

void initLed() {
    LED_DDR = 0xff;
    offAllLed();
}

void onLed(int num) {
    if (num == 4)
        offAllLed();

    switch (num) {
        case 1:
            LED_PORT = (1 << LED1);
        case 2:
            LED_PORT = (1 << LED2);
        case 3:
            LED_PORT = (1 << LED3);
    }
}