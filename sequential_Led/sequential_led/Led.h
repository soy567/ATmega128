#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR		DDRD
#define LED_PORT	PORTD

#define	LED1	0
#define LED2	1
#define LED3	2
#define LED4	3
#define LED5	4
#define LED6	5
#define LED7	6
#define LED8	7

void ledbar();
void leftShift();
void rightShift();
void toggle();
void setLedData(uint8_t data);
void initLed();
uint8_t getLedData();
void writeLedData(uint8_t data);
void onAllLed();
void offAllLed();

#endif /* LED_H_ */