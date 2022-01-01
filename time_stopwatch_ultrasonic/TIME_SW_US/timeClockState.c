#include "timeClockState.h"

struct _timeClock stTimeClock;  // _timeClock 구조체 선언

// 시계 실행함수 정의
void timeClockExcute() {
    // FND로 데이터 보내 시간 출력시킴으로써 시계 실행
    setFndData(stTimeClock.min * 100 + stTimeClock.sec);
}