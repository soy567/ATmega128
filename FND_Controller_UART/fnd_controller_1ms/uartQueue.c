#include "uartQueue.h"

uint8_t rxBuff[100] = {0};
uint8_t rxFlag = 0;  // 데이터 수신완료 Flag

void setRxFlag() {
    rxFlag = 1;
}

void clearRxFlag() {
    rxFlag = 0;
}

uint8_t getRxFlag() {
    return rxFlag;
}

uint8_t *getRxBuff() {
    return rxBuff;
}

void uartQueue_ISR_Process() {
    static uint8_t tail = 0;
    uint8_t rxData = UART0_receive();

    if (rxData == ';') {
        rxBuff[tail] = '\0';
        tail = 0;
        setRxFlag();
    } else {
        rxBuff[tail] = rxData;
        tail++;
    }
}