#ifndef TIMECLOCKSTATE_H_
#define TIMECLOCKSTATE_H_

#include <avr/io.h>
#include "Button.h"
#include "timeClock.h"
#include "Fnd.h"

// timeClockState.c에서 선언된 stTimeClock 변수 
// 외부에서도 사용할 수 있도록 extern 선언
extern struct _timeClock stTimeClock;

void timeClockExcute(); // 시계 시작 함수

#endif /* TIMECLOCKSTATE_H_ */