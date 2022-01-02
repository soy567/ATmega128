#include "led.h"

void ledInit() {
    LED_DDR = 0xff;
    LED_PORT &= ~((1 << LED1) | (1 << LED2) | (1 << LED3));
}

void onLed(uint8_t num) {
    LED_PORT = (1 << num);
}