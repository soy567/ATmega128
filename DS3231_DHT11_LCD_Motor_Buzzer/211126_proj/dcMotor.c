#include "dcMotor.h"

char buff[30];

void initMotor() {
	DDRB |= (1<<PB5);
	// TIM1 분주비 8
	TCCR1B |= (1<<CS11);
	// TIM1 Fast PWM Mode설정, TOP = ICR1
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	ICR1 = 1000 - 1; // Top값 설정하여 분주비 설정 (2kHz)
	// 출력설정
	TCCR1A |= (1<<COM1A1);
	OCR1A = 400;
}

void motorExcute() {
	// duty rate 40 -> 65 -> 85 -> 95 -> 0
	switch (OCR1A) {
		case 400 : OCR1A = 650; break;
		case 650 : OCR1A = 850; break;
		case 850 : OCR1A = 950; break;
		case 950 : OCR1A = 0; break;
		default : OCR1A = 400; break;
	}
	sprintf(buff, "%2d%%", OCR1A / 10);
	LCD_WriteStringXY(1, 12, buff);
}