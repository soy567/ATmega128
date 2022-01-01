#ifndef TIMECLOCK_H_
#define TIMECLOCK_H_

#include <avr/io.h>

// 시간 저장할 구조체 정의
struct _timeClock {
	int hour;
	int min;
	int sec;
	int msec;
	int ms;
};

// 시간 관리할 함수 정의
void incMSec(struct _timeClock *stClock);
void setTimeClock(struct _timeClock *stClock, int hh, int mm, int ss, int msec, int ms);

#endif /* TIMECLOCK_H_ */