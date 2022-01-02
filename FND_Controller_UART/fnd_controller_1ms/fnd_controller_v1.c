#include "fnd_controller_v1.h"

uint8_t fnd_data = 0;   // [7:0]
uint16_t fndValue = 0;  // 0~65535 값 표현가능

// en -> 6, select -> 4~5, data -> 0~3, 어떤 값과 and '1' 연산 -> 원래 값 출력
void fnd_ISR_Process() {
    static uint8_t fndDigitState = 0;  // 함수가 scope 에서 벗어나도 값 유지되도록 static 으로 지정
    uint16_t fndData;
    fndDigitState = (fndDigitState + 1) % 6;  // 4로 나누어 4이상 되지않도록 범위 지정

    fndData = fnd_getData();
    switch (fndDigitState) {
        case 0:
            fnd_setData(0, fndData / 1000 % 10);
            break;
        case 1:
            fnd_setData(1, fndData / 100 % 10);
            break;
        case 2:
            fnd_setData(2, fndData / 10 % 10);
            break;
        case 3:
            fnd_setData(3, fndData % 10);
            break;
        case 4:
            fnd_setData(0, 10);
            break;  // 1000 자리 dp
        case 5:
            fnd_setData(2, 10);
            break;  // 10 자리 dp
    }
}

void fnd_writeData(uint16_t data) {
    // if (data >= 10000) data = 9999; // 데이터 범위 예외처리
    fndValue = data;
}

uint16_t fnd_getData() {
    return fndValue;
}

void fnd_enable() {
    // fnd_data & 0b10111111 -> 6번 비트 빼고 나머지 비트는 모두 기존 값 유지, 6번 비트는 0으로 설정,
    // Masking (데이터 설정할 위치의 비트 0으로 설정, 원하는 데이터 or 연산 하여 반영하기 위해)
    fnd_data = (fnd_data & 0b10111111) | (1 << 6);  // en pin '1' setting
    FND_PORT = fnd_data;                            // 출력
}

void fnd_disable() {
    fnd_data = (fnd_data & 0b10111111) & ~(1 << 6);  // all '0' setting
    FND_PORT = fnd_data;                             // 출력
}

void fnd_init() {
    FND_DDR = 0xff;   // 포트의 핀을 모두 출력으로 설정
    FND_PORT = 0x00;  // 포트의 모든 핀 0v 출력

    // timer0 Interrupt 설정
    TCCR0 |= (1 << CS02);   // prescaler 분주비 64로 설정
    TCCR0 |= (1 << WGM01);  // 타이머/카운트 CTC모드로 설정
    TIMSK |= (1 << OCIE0);  // OC Interrupt OCR0값, timer 0의 비교일치 인터럽트 활성화
    OCR0 = 250 - 1;         // timer 1 비교 인터럽트 Top값 설정하여 1ms 간격으로 인터럽트 발생 (분주비가 64일때)
}

void fnd_setData(uint8_t digit, uint8_t fndData) {
    if (digit > 3) digit = 3;
    if (fndData > 10) fndData = 0;

    fnd_data = (fnd_data & 0b11001111) | (digit << 4);  // select (00)
    fnd_data = (fnd_data & 0b11110000) | fndData;       // 4fnd data ([3:0])
    FND_PORT = fnd_data;                                // 출력
}