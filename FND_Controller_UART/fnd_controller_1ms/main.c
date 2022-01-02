#include "main.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect) {
    fnd_ISR_Process();
}

// 1ms 간격으로 timer2 비교 인터럽트 실행
ISR(TIMER2_COMP_vect) {
    stopWatch_ISR_Process();
}

// FND 자릿수 바꿔주는 인터럽트 함수 작동
ISR(TIMER0_COMP_vect) {
    fnd_ISR_Process();
}

// uart 데이터 송신시 인터럽트
ISR(USART0_RX_vect) {
    uart_ISR_Process();
}

int main(void) {
    UART0_init();
    fnd_init();
    stopWatchInit();

    stdout = &OUTPUT;  // stdout에 OUTPUT 주소 입력

    sei();  // global inturrupt 실행명령

    fnd_enable();

    while (1) {
        stopWatchExcute();
    }
}
