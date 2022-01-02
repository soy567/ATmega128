#include "Buzzer.h"

void BuzzerInit() {
	BUZZER_DDR |= (1<<BUZZER);
	
	// TIM3 사용, OC3A, Fast PWM 14mode, TOP->ICR3, Duty Cycle = 50%, 비반전 모드
	TCCR3B |= (1<<CS31); // prescaler = 8분주
	// Fast PWM 14mode
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM33) | (1<<WGM32);
}

void BuzzerSound(uint16_t note) {
	
	if (note > 65500) note = 65500;
	
	// TOP 설정 ICR3 16bit (0~65535)
	BUZZER_TOP = (2000000 / note) - 1;
	// Duty rate 설정
	OCR3A = (ICR3 / 2) - 1;
}

void BuzzerOn() {
	// 비반전모드 PWM OC3A 출력
	TCCR3A |= (1<<COM3A1);
}

void BuzzerOff() {
	// 비반전모드 PWM OC3A 출력 차단
	TCCR3A &= ~(1<<COM3A1);
}

void BuzzerPowerOn() {
	
}

void BuzzerButton1() {
	BuzzerOn();
	BuzzerSound(1568);
	_delay_ms(100);
	BuzzerSound(1480);
	_delay_ms(100);
	BuzzerOff();
}