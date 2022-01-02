#include "main.h"

// UART로 Serial 데이터 출력하기 위한 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

uint8_t state = TimeClock;

// FND 자릿수 바꿔주는 인터럽트 함수 작동
ISR(TIMER0_COMP_vect) {
    fnd_ISR_Process();
}

ISR(TIMER2_COMP_vect) {
    stopWatch_ISR_Process();
}

ISR(USART0_RX_vect) {
    uartQueue_ISR_Process();
}

int main(void) {
    I2C_Init();
    UART0_init();
    stopWatchInit();
    buttonInit();
    fnd_init();
    fnd_enable();
    ledInit();

    sei();

    stdout = &OUTPUT;  // UART로 printf 사용하기 위한 설정

    while (1) {
        // Event 처리
        switch (state) {
            case TimeClock:
                if (getButton4State()) state = StopWatch;
                break;
            case StopWatch:
                if (getButton4State()) state = TimeClock;
                break;
        }
        // 실행 처리
        switch (state) {
            case TimeClock:
                onLed(0);
                DS3231Excute();
                break;
            case StopWatch:
                onLed(1);
                stopWatchExcute();
                break;
        }
    }
}