#ifndef TIMECLOCKSTATE_H_
#define TIMECLOCKSTATE_H_

#include <avr/io.h>
#include "Button.h"
#include "timeClock.h"
#include "Fnd.h"

// 외부의(timeClock.h) 구조체인 _timeClock 사용을 알림
extern struct _timeClock stTimeClock;

void timeClockExcute(); // 시계 시작 함수

#endif /* TIMECLOCKSTATE_H_ */