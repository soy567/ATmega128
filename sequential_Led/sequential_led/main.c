#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Button.h"
#include "Led.h"

enum {eLeftShitf, eRightShift};			// enum 이용하여 프로그램이 가질 수 있는 상태 정의

int main(void)
{
    uint8_t ledstateMachine = eLeftShitf;	// main의 상태 저장할 변수
	
    // 초기화 코드
    initLed();
    buttonInit();
    setLedData(0x01); 
	
    while (1) 
    {
	switch(ledstateMachine) {	// switch문 사용하여 상태 구분, 실행 로직 정의
	    case eLeftShitf:		
	        leftShift();
		if (getButton1State()) {	// 버튼 이용하여 다른 상태로 전환
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
	_delay_ms(100);		// 100ms 딜레이
    }
}

