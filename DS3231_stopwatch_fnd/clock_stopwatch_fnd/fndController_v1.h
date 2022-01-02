
#ifndef FNDCONTROLLER_V1_H_
#define FNDCONTROLLER_V1_H_

#include <avr/io.h>

#define FND_DDR		DDRF
#define FND_PORT	PORTF

void fnd_ISR_Process();
void fnd_writeData(uint16_t data);
uint16_t fnd_getData();
void fnd_enable();
void fnd_disable();
void fnd_setData(uint8_t digit, uint8_t fndData);
void fnd_init();

#endif /* FNDCONTROLLER_V1_H_ */