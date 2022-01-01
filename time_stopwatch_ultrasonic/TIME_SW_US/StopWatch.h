#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <avr/io.h>
#include "Button.h"
#include "timeClock.h"
#include "Fnd.h"

// 열거형 이용하여 스톱워치의 3가지 상태 정의
enum {
    eStopWatchStop,
    eStopWatchRun,
    eStopWatchReset
};

// extern -> 외부의 변수 사용을 알림 (timeClock.h 파일과 링킹 됨)
extern struct _timeClock stStopWatch;

// 스탑워치에 필요한 함수헤더 정의 (헤더파일만 import 하여 사용하기 위해 정의)
void setStopWatchState(int state);
int getStopWatchState();
void stopWatchStop();
void stopWatchRun();
void stopWatchReset();
void stopWatchExcute();

#endif /* STOPWATCH_H_ */