// UART 통신 이용하여 여러 데이터 입력받기 위한 Queue
#include "uartQueue.h"

uint8_t rxBuff[100] = {
    0,
};
uint8_t rxFlag = 0;

uint8_t *getRxBuff() {
    return &rxBuff[0];
}

void setRxFlag() {
    rxFlag = 1;
}

void clearRxFlag() {
    rxFlag = 0;
}

uint8_t getRxFlag() {
    return rxFlag;
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