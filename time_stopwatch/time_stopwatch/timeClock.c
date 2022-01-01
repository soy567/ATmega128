#include "timeClock.h"

// 시간 구조체 값 수정하는 함수
void setTimeClock(struct _timeClock *stClock, int hh, int mm, int ss, int msec, int ms) {
    stClock->hour = hh;
    stClock->min = mm;
    stClock->sec = ss;
    stClock->msec = msec;
    stClock->ms = ms;
}

// 시간 계산하는 함수 (1ms 마다 실행  24:00:00 까지 측정가능)
void incMSec(struct _timeClock *stClock) {
    stClock->ms++;  // 실행시 ms증가

    if (stClock->ms >= 100)  // 100ms 도달시
    {
        stClock->ms = 0;         // ms = 0 초기화
        stClock->msec++;         // 100ms 측정하는 msec 증가
        if (stClock->msec > 10)  // 1000ms -> 1s 도달시
        {
            stClock->msec = 0;  // msec = 0 초기화
            stClock->sec++;     // sec 증가
        }

        if (stClock->sec >= 60)  // 60s 도달시
        {
            stClock->sec = 0;        // sec = 0 초기화
            stClock->min++;          // min 증가
            if (stClock->min >= 60)  // 60m 도달시
            {
                stClock->min = 0;         // min = 0 초기화
                stClock->hour++;          // hour 증가
                if (stClock->hour >= 24)  // 24h 도달시
                {
                    stClock->hour = 0;  // hour = 0 초기화
                }
            }
        }
    }
}
