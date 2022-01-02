#ifndef UART0_H_
#define UART0_H_

#include <avr/io.h>

void UART0_init(void);
void UART0_transmit(unsigned char data);
unsigned char UART0_receive(void);
void UART0_print_string(char *str);

#endif /* UART0_H_ */