#include "stopWatch.h"

uint8_t swState = STOP;
uint8_t fnd_blight_state = FND_ON;

struct _time stTime = {
    0,
};

void stopWatchInit() {
    TCCR2 |= (1 << CS21) | (1 << CS20);  // 분주비 64
    TCCR2 |= (1 << WGM21);               // CTC mode
    TIMSK |= (1 << OCIE2);               // OC Interrupt Enable, TCNT2 OCR2값 같아졌을때 인터럽트 발생
    OCR2 = 250 - 1;                      // 1ms 간격으로 인터럽트 발생(분주기64)
}

void stopWatch_ISR_Process() {
    if (swState == RUN)
        stTime.ms++;

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
}

void stopWatchExcute() {
    // Event 처리 코드
    switch (fnd_blight_state) {
        case FND_ON:
            if (getButton3State())
                fnd_blight_state = FND_OFF;

            if (getRxFlag() == 1) {
                uint8_t* pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "FND_OFF", 7) == 0) {
                    printf("Stop Watch FND_OFF!\n");
                    fnd_blight_state = FND_OFF;
                    clearRxFlag();
                }
            }
            break;
        case FND_OFF:
            if (getButton3State())
                fnd_blight_state = FND_ON;

            if (getRxFlag() == 1) {
                uint8_t* pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "FND_ON", 6) == 0) {
                    printf("Stop Watch FND_ON!\n");
                    fnd_blight_state = FND_ON;
                    clearRxFlag();
                }
            }
            break;
    }
    // 실행 코드
    switch (fnd_blight_state) {
        case FND_ON:
            fnd_enable();
            break;
        case FND_OFF:
            fnd_disable();
            break;
    }

    // Event 처리 코드
    switch (swState) {
        case STOP:
            if (getButton1State()) {
                swState = RUN;  // run state
            } else if (getButton2State()) {
                swState = RESET;  // reset state
            }

            if (getRxFlag() == 1) {
                uint8_t* pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "RUN", 3) == 0) {
                    printf("Stop Watch RUN!\n");
                    swState = RUN;
                    clearRxFlag();
                } else if (strncmp(pRxBuff, "RESET", 5) == 0) {
                    printf("Stop Watch RESET!\n");
                    swState = RESET;
                    clearRxFlag();
                }
            }
            break;

        case RUN:
            if (getButton1State()) swState = STOP;

            if (getRxFlag() == 1) {
                uint8_t* pRxBuff = getRxBuff();
                if (strncmp(pRxBuff, "STOP", 4) == 0) {
                    printf("Stop Watch STOP!\n");
                    swState = STOP;
                    clearRxFlag();
                }
            }
            break;

        case RESET:
            swState = STOP;
            break;
    }

    // 실행코드
    switch (swState) {
        case STOP:  // stop state
            fnd_writeData(stTime.min * 1000 + stTime.sec * 10 + stTime.hms);
            break;
        case RUN:  // run state
            fnd_writeData(stTime.min * 1000 + stTime.sec * 10 + stTime.hms);
            printf("%02d:%02d:%02d \n", stTime.min, stTime.sec, stTime.hms);
            break;
        case RESET:  // reset state
            stTime.hms = 0;
            stTime.sec = 0;
            stTime.min = 0;
            stTime.hour = 0;
            fnd_writeData(stTime.min * 1000 + stTime.sec * 10 + stTime.hms);
            printf("%02d:%02d:%d \n", stTime.min, stTime.sec, stTime.hms);
            break;
    }
    //clearRxFlag();
}
