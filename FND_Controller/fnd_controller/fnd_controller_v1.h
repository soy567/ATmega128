#ifndef FND_CONTROLLER_V1_H_
#define FND_CONTROLLER_V1_H_

#include <avr/io.h>

#define FND_DDR DDRD
#define FND_PORT PORTD

void fnd_ISR_Process();
void fnd_writeData(uint16_t data);
uint16_t fnd_getData();
void fnd_enable();
void fnd_disable();
void fnd_init();
void fnd_setData(uint8_t digit, uint8_t fndData);

#endif /* FND_CONTROLLER_V1_H_ */