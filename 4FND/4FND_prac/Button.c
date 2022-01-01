#include "Button.h"

void buttonInit() {
	BUTTON_DDR &= ~((1<<BUTTON1) | (1<<BUTTON2));
}

uint8_t getButton1State() {
	static uint8_t prevButton1State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1<<BUTTON1);
	
	if (prevButton1State != PUSHED && curButtonState == PUSHED) {
		prevButton1State = PUSHED;
		return FALSE;
	}
	else if (prevButton1State == PUSHED && curButtonState != PUSHED) {
		prevButton1State = RELEASED;
		return TRUE;
	}
	return FALSE;
}

uint8_t getButton2State() {
	static uint8_t prevButton2State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1<<BUTTON2);
	
	if (prevButton2State != PUSHED && curButtonState == PUSHED) {
		prevButton2State = PUSHED;
		return FALSE;
	}
	else if (prevButton2State == PUSHED && curButtonState != PUSHED) {
		prevButton2State = RELEASED;
		return TRUE;
	}
	return FALSE;
}

uint8_t getButton3State() {
	static uint8_t prevButton3State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1<<BUTTON2);
	
	if (prevButton3State != PUSHED && curButtonState == PUSHED) {
		prevButton3State = PUSHED;
		return FALSE;
	}
	else if (prevButton3State == PUSHED && curButtonState != PUSHED) {
		prevButton3State = RELEASED;
		return TRUE;
	}
	return FALSE;
}
