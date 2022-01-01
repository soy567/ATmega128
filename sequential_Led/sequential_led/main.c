#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Button.h"
#include "Led.h"

enum {eLeftShitf, eRightShift};

int main(void)
{
    uint8_t ledstateMachine = eLeftShitf;
	
	// 초기화 코드
	initLed();
	buttonInit();
	setLedData(0x01); 
	
    while (1) 
    {
		switch(ledstateMachine) {
			case eLeftShitf:
			leftShift();
			if (getButton1State()) {
				ledstateMachine = eRightShift;
			}
			break;
			
			case eRightShift:
			rightShift();
			if (getButton1State()) {
				ledstateMachine = eLeftShitf;
			}
			break;
		}
		_delay_ms(100);
    }
}

