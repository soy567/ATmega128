#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

#define BUTTON_DDR	DDRC
#define BUTTON_PIN	PINC

#define BUTTON1	0
#define BUTTON2	1
#define BUTTON3	2
#define BUTTON4	3

#define RELEASED 1 // 누르지 않았을 때 MCU로 high 입력
#define PUSHED 0 // 버튼 눌렸을 때 MCU로 low 입력
#define TRUE 1
#define FALSE 0

void buttonInit();
uint8_t getButton1State();
uint8_t getButton2State();

#endif /* BUTTON_H_ */