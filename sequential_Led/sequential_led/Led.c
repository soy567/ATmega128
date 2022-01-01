#include "Led.h"

#include "Button.h"

uint8_t ledData;  // led bar 의 속성 저장할 변수

void setLedData(uint8_t data) {
    if (data > 0xff)
        data = 0xff;
    else if (data < 0)
        data = 0;
    ledData = data;
}

uint8_t getLedData() {
    return ledData;
}

void ledbar() {
    LED_DDR = 0xff;
}

void writeLedData(uint8_t data) {
    LED_PORT = data;
}

void initLed() {
    // LED_DDR = 0xff;
    LED_DDR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) | (1 << LED5) | (1 << LED6) | (1 << LED7) | (1 << LED8);
}

void onAllLed() {
    LED_PORT = 0xff;
}

void offAllLed() {
    LED_PORT = 0x00;
}

// 순차점멸 함수 정의
void toggle() {
    uint8_t ledState = 0x01;

    // 1번 부터 순서대로 점멸
    for (int i = 0; i < 7; i++) {
        ledState = 0x01;
        LED_PORT = ledState << i;
        _delay_ms(100);
    }

    // 8번째 부터 거꾸로 점멸
    for (int i = 0; i < 7; i++) {
        ledState = 0x80;
        LED_PORT = ledState >> i;
        _delay_ms(100);
    }
}

void leftShift() {
    ledData = (ledData << 1) | (ledData >> 7);  // 원형 left 시프트
    writeLedData(ledData);                      // 시프트 하여 데이터 쓰기
}

void rightShift() {
    ledData = (ledData >> 1) | (ledData << 7);  // 원형 right 시프트
    writeLedData(ledData);
}