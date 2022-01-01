#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "fnd.h"
#include "Button.h"

enum {eFndInc, eFndDec};

int main(void) {
	// 초기화 함수
	fndInit();
	int16_t count = 0;
	uint8_t fndStateMachine = eFndInc;
	
    while (1) {
		switch(fndStateMachine) {
			case eFndInc: {
				count++;
				if (count >= 10000) count = 0;
				fndDisplayData(count); // 카운트 한 숫자 FND에 출력
				_delay_ms(5);
				
				if (getButton1State()) {
					fndStateMachine = eFndDec;
				}
				break;
			}
			
			case eFndDec: {
				count--;
				if (count <= 0) {
					count = 9999;
				}
				fndDisplayData(count);
				_delay_ms(5);
				
				if (getButton1State()) {
					fndStateMachine = eFndInc;
				}
				break;
			}	
		}
    }
}

