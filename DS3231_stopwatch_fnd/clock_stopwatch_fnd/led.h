#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

#define LED_DDR		DDRA
#define LED_PORT	PORTA

#define LED1	0
#define LED2	1
#define LED3	2

void ledInit();
void onLed(uint8_t num);

#endif /* LED_H_ */