/*
// 이벤트, 실행 코드 분리하지 않은 main 문 
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Button.h"
#include "fnd_controller_v1.h"

ISR(TIMER0_OVF_vect) {
	fnd_ISR_Process();
}

int main(void) {
	fnd_init();
	
	// timer0 Interrupt 설정
	TCCR0 |= (1<<CS02); // prescaler 분주비 64로 설정 
	TIMSK |= (1<<TOIE0); // timer 0의 오버플로우 인터럽트 활성화
	
	sei(); // global inturrupt 실행명령
	fnd_enable();
	uint16_t fnd_value = 0;
	uint8_t state = 0;
	
    while (1) {
		switch (state) {
			case 0 :
				if (getButton1State()) state = 1; // run state
				else if (getButton2State()) state = 2; // reset state
				else if (getButton3State()) state = 3; // go to fnd off state
				break; // stop state
			
			case 1 :
				fnd_writeData(fnd_value);
				_delay_ms(100);
				fnd_value++;
				if(fnd_value >= 10000) fnd_value = 0;
			
				if (getButton1State()) state = 0;
				else if (getButton3State()) state = 3; // go to fnd off state
				break; // run state
			
			case 2 :
				fnd_value = 0;
				fnd_writeData(fnd_value);
				state = 0;
				break; // reset state
			
			// fnd off case
			case 3 :
				fnd_value = 0;
				fnd_writeData(fnd_value);
				fnd_disable();
			
				if (getButton3State()) {
					fnd_enable();
					state = 0;
				}
				break;
		}
	}
}
*/