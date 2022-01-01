#include "Button.h"

void buttonInit() {
	BUTTON_DDR &= ~((1<<BUTTON1) | (1<<BUTTON2));
}

void getButton1State() {
	static uint8_t prevButton1State = RELEASED;
	uint8_t curButton1State = BUTTON_PIN | (1<<BUTTON1);
	
	if (prevButton1State != PUSHED && curButton1State == PUSHED) {
		prevButton1State = PUSHED;
		return FALSE;
	}
	else if (prevButton1State == PUSHED && curButton1State != PUSHED) {
		prevButton1State = RELEASED;
		return TRUE;
	}
	return FALSE;
}

void getButton2State() {
	static uint8_t prevButton2State = RELEASED;
	uint8_t curButton1State = BUTTON_PIN | (1<<BUTTON2);
	
	if (prevButton2State != PUSHED && curButton1State == PUSHED) {
		prevButton2State = PUSHED;
		return FALSE;
	}
	else if (prevButton2State == PUSHED && curButton1State != PUSHED) {
		prevButton2State = RELEASED;
		return TRUE;
	}
	return FALSE;
}
