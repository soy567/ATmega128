#include "fndController_v1.h"

uint8_t fnd_data = 0;
uint16_t fndValue = 0;  // 0 ~ 65535

void fnd_ISR_Process() {
    static uint8_t fndDigitState = 0;
    uint16_t fndData;
    fndDigitState = (fndDigitState + 1) % 6;  // 4로 나눈 나머지

    fndData = fnd_getData();
    switch (fndDigitState) {
        case 0:
            fnd_setData(0, fndData / 1000 % 10);  // 1000자리
            break;
        case 1:
            fnd_setData(1, fndData / 100 % 10);  // 100자리
            break;
        case 2:
            fnd_setData(2, fndData / 10 % 10);  // 10자리
            break;
        case 3:
            fnd_setData(3, fndData % 10);  // 1자리
            break;
        case 4:
            fnd_setData(0, 10);  // 1000자리 dp
            break;
        case 5:
            fnd_setData(2, 10);  // 10자리 dp
            break;
    }
}

void fnd_writeData(uint16_t data) {
    //if (data >= 10000) data = 9999;
    fndValue = data;
}

uint16_t fnd_getData() {
    return fndValue;
}

void fnd_enable() {
    fnd_data = (fnd_data & 0b10111111) | (1 << 6);  // en pin
    FND_PORT = fnd_data;
}

void fnd_disable() {
    fnd_data = (fnd_data & 0b10111111) & ~(1 << 6);  // en pin
    FND_PORT = fnd_data;
}

void fnd_setData(uint8_t digit, uint8_t fndData) {
    if (digit > 3) digit = 3;
    if (fndData > 10) fndData = 0;

    fnd_data = (fnd_data & 0b11001111) | (digit << 4);  // select
    fnd_data = (fnd_data & 0b11110000) | fndData;       // fnd data
    FND_PORT = fnd_data;
}

void fnd_init() {
    FND_DDR = 0xff;   // 출력 설정
    FND_PORT = 0x00;  // 0v를 PD 8개핀에 출력하겠다.

    // timer0 interrupt 설정
    TCCR0 |= (1 << CS02);   // 분주비 64
    TCCR0 |= (1 << WGM01);  // CTC mode
    TIMSK |= (1 << OCIE0);  // OC Interrupt Enable, TCNT0 OCR0값 같아졌을때 인터럽트 발생
    OCR0 = 250 - 1;         // 1ms 간격으로 인터럽트 발생(분주기64)
}
