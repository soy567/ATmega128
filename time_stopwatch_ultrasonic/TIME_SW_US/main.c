
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Button.h"
#include "Fnd.h"
#include "Led.h"
#include "StopWatch.h"
#include "UltraSonic.h"
#include "timeClockState.h"

// 타이머0 오버플로우 인터럽트 서비스루틴
ISR(TIMER0_OVF_vect) {
    TCNT0 = 6;  // 1ms 간격으로 인터럽트 발생
    if (getStopWatchState() == eStopWatchRun) {
        incMSec(&stStopWatch);  // 스톱워치 시간계산 시작
    }
    incMSec(&stTimeClock);  // 시계 시간계산 시작
    fndISRProcess();
}

// Interrupt 0 설정 (초음파 센서)
ISR(INT0_vect) {
    if (US_PIN & (1 << US_ECHO)) {
        US_ClearTimer();
        US_StartTimer();
        US_EchoFallingEdge();
    } else {
        US_getTimer();
        US_StopTimer();
        US_EchoRisingEdge();
        US_SetRxFlag();
    }
}

// Timer 0 레지스터 설정 (주기 1ms인 clk생성 설정)
void timerInt1MsInit() {
    TCCR0 |= (1 << CS02);  // | (1<<CS01) | (1<<CS00);
    TIMSK |= (1 << TOIE0);
    TCNT0 = 6;
}

enum {
    eTimeClockState,
    eStopWatchState,
    eUltraSonicState
};

int main(void) {
    int deviceState = eTimeClockState;
    timerInt1MsInit();
    initLed();
    fndInit();
    buttonInit();
    US_Init();

    sei();

    uint16_t distance;

    while (1) {
        switch (deviceState) {
            case eTimeClockState:
                timeClockExcute();
                onLed(1);
                if (getButton1State()) {
                    deviceState = eStopWatchState;
                }

            case eStopWatchState:
                stopWatchExcute();
                onLed(2);
                if (getButton1State()) {
                    deviceState = eUltraSonicState;
                }

            case eUltraSonicState:
                onLed(3);
                if (getButton1State()) {
                    deviceState = eTimeClockState;
                } else if (getButton2State()) {
                    US_Trigger();  //us trigger 시작.
                }

                if (US_getRxFlag())  //대기
                {
                    US_ClearRxFlag();
                    distance = US_Distance();  // 거리계산 cm
                    setFndData(distance);      //FND 출력
                }
        }
    }
}
