#ifndef UARTQUEUE_H_
#define UARTQUEUE_H_

#include <avr/io.h>
#include "uart0.h"

void setRxFlag();
void clearRxFlag();
uint8_t getRxFlag();
uint8_t *getRxBuff();
void uartQueue_ISR_Process();


#endif /* UARTQUEUE_H_ */