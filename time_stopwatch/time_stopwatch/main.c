#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Button.h"
#include "Fnd.h"
#include "timeClock.h"
#include "StopWatch.h"
#include "timeClockState.h"

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6; // 1ms 간격으로 인터럽트 발생
	// 스톱워치 작동상태이면
	if (getStopWatchState() == eStopWatchRun)
	{
		incMSec(&stStopWatch); // 스톱워치 시간계산 시작
	}
	incMSec(&stTimeClock); // 시계 시간계산 시작
	fndISRProcess();
}

// 인터럽트 초기화 함수
void timerInt1MsInit()
{
	TCCR0 |= (1 << CS02); // | (1<<CS01) | (1<<CS00);
	TIMSK |= (1 << TOIE0);
	TCNT0 = 6;
}

enum
{
	eTimeClockState,
	eStopWatchState
}; // 상태 나타내기 위해 enum 사용

int main(void)
{
	uint8_t digitalClockState = eTimeClockState; // 스톱워치, 시계 상태 구분 변수 정의
	timerInt1MsInit();
	fndInit();
	buttonInit();
	sei(); // 인터럽트 작동

	while (1)
	{
		switch (digitalClockState) // 시계 상태에 따라
		{
		case eTimeClockState:	   // 시계모드인 경우
			timeClockExcute();	   // 시계 시작
			if (getButton3State()) // 버튼 3이 눌린경우
			{
				digitalClockState = eStopWatchState; // 모드변경
			}
			break;
		case eStopWatchState:	   // 스톱워치 모드인 경우
			stopWatchExcute();	   // 스톱워치 시작
			if (getButton3State()) // 버튼 3이 눌린경우
			{
				digitalClockState = eTimeClockState; // 모드변경
			}
			break;
		}
	}
}
