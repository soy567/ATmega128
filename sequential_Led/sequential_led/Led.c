#include "Led.h"

#include "Button.h"

uint8_t ledData;  // led bar 의 속성 저장할 변수

// LED Driver 내부 변수 Setter
void setLedData(uint8_t data) {
    if (data > 0xff)    // 범위 초과한 경우
        data = 0xff;    // 모든 LED 켜기
    else if (data < 0)  // 최솟값 이하인 경우
        data = 0;       // 모든 LED 끄기
    ledData = data;     // 입력받은 데이터 ledData에 저장
}

// LED Driver 내부 변수 Getter
uint8_t getLedData() {  
    return ledData;
}

// LED 연결된 PORT 방향 Register 모두 출력으로 설정
void ledbar() {
    LED_DDR = 0xff;
}

// LED 연결된 PORT(8-output)에 데이터 입력하여 원하는 포트만 High 출력
void writeLedData(uint8_t data) {
    LED_PORT = data;
}

// LED 초기화
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
