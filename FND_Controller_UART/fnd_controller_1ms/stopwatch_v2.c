#include <stdio.h>
#include <string.h>

#include "stopwatch.h"

uint8_t state = STOP;
uint8_t fnd_blight_state = FND_ON;

struct _time stTime = {
    0,
};

void stopWatchInit() {
    // timer 2 Interrupt 설정
    TCCR2 |= (1 << CS21) | (1 << CS20);  // prescaler 분주비 64로 설정
    TCCR2 |= (1 << WGM21);               // 타이머 카운트 CTC모드로 설정
    TIMSK |= (1 << OCIE2);               // timer 2의 비교일치 인터럽트 활성
    OCR2 = 250 - 1;                      // timer 2 비교 인터럽트 TOP 값 설정
}

void stopWatch_ISR_Process() {
    if (state == RUN) {
        if (stTime.ms >= 100 - 1) {
            stTime.ms = 0;
            stTime.hms++;
            if (stTime.hms >= 10) {
                stTime.hms = 0;
                stTime.sec++;
                if (stTime.sec >= 60) {
                    stTime.sec = 0;
                    stTime.min++;
                    if (stTime.min >= 60) {
                        stTime.min = 0;
                        stTime.hour++;
                        if (stTime.hour >= 24) stTime.hour = 0;
                    }
                }
            }
        }
        stTime.ms++;
    }
}

void stopWatchExcute() {
    // Event 처리 code
    switch (fnd_blight_state) {
        case FND_ON:
            if (getButton3State()) fnd_blight_state = FND_OFF;
            if (getRxFlag() == 1) {
                uint8_t *pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "FND_OFF", 7) == 0) {
                    printf("Stop Watch FND Off!\n");
                    fnd_blight_state = FND_OFF;
                    clearRxFlag();
                }
            }
            break;

        case FND_OFF:
            if (getButton3State()) fnd_blight_state = FND_ON;
            if (getRxFlag() == 1) {
                uint8_t *pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "FND_ON", 6) == 0) {
                    printf("Stop Watch FND On!\n");
                    fnd_blight_state = FND_ON;
                    clearRxFlag();
                }
            }
            break;
    }

    switch (state) {
        case STOP:
            if (getButton1State())
                state = RUN;  // run state
            else if (getButton2State())
                state = RESET;  // reset state
            if (getRxFlag() == 1) {
                uint8_t *pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "RUN", 3) == 0) {
                    printf("Stop Watch RUN!\n");
                    state = RUN;
                    clearRxFlag();
                } else if (strncmp(pRxBuff, "RESET", 5) == 0) {
                    printf("Stop Watch RESET!\n");
                    state = RESET;
                    clearRxFlag();
                }
            }
            break;

        case RUN:
            if (getButton1State()) state = STOP;
            if (getRxFlag() == 1) {
                uint8_t *pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "STOP", 4) == 0) {
                    printf("Stop Watch STOP!\n");
                    state = STOP;
                    clearRxFlag();
                }
            }
            break;

        case RESET:
            state = STOP;
            break;
    }

    // 실행 code
    switch (fnd_blight_state) {
        case FND_ON:
            fnd_enable();
            break;
        case FND_OFF:
            fnd_disable();
            break;
    }
    switch (state) {
        case STOP:
            break;  // stop state

        case RUN:  // run state
            fnd_writeData(stTime.min * 1000 + stTime.sec * 10 + stTime.hms);
            break;

        case RESET:
            // count = 0;
            stTime.ms = 0;
            stTime.hms = 0;
            stTime.sec = 0;
            stTime.min = 0;
            stTime.hour = 0;
            fnd_writeData(stTime.min * 1000 + stTime.sec * 10 + stTime.hms);
            state = STOP;
            break;  // reset state
    }
    clearRxFlag();
}