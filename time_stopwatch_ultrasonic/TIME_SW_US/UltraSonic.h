#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define US_DDR		DDRD
#define US_PORT		PORTD
#define US_PIN		PIND
#define US_ECHO		0
#define US_TRIG		1

void US_getTimer();
void US_EchoFallingEdge();
void US_EchoRisingEdge();
void US_ClearTimer();
void US_StartTimer();
void US_StopTimer();
void US_Init();
void US_Trigger();
uint16_t US_Distance();
int US_getRxFlag();
void US_ClearRxFlag();
void US_SetRxFlag();


#endif /* ULTRASONIC_H_ */