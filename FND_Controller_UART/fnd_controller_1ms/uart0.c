#include "uart0.h"

void UART0_init(void) {
    UBRR0H = 0x00;
    UBRR0L = 16;  // 115200 baud rate (data sheet)
    UCSR0A |= (1 << U2X0);

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);  // Tx Rx 모두 사용

    UCSR0B |= (1 << RXCIE0);  // 수신 Rx UART0 인터럽트 Enable
}

void UART0_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)))
        ;  // 송신 가능 대기
    UDR0 = data;
}

unsigned char UART0_receive(void) {
    while (!(UCSR0A & (1 << RXC0)))
        ;  // 데이터 수신 대기
    return UDR0;
}

void UART0_print_string(char *str) {
    for (int i = 0; str[i]; i++) {
        UART0_transmit(str[i]);
    }
}