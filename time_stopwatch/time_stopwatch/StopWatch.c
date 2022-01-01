#include "StopWatch.h"

// 값 모두 0으로 구조체 생성
struct _timeClock stStopWatch = {
	0,
};

int stopWatchState = eStopWatchStop; // 스톱워치 상태 저장할 변수 정의

void setStopWatchState(int state) // 스톱워치 상태 변경함수
{
	stopWatchState = state;
}

int getStopWatchState() // 스톱워치 상태 가져오는 함수
{
	return stopWatchState;
}

void stopWatchStop() // 스톱워치 멈추는 함수
{
	setFndData(stStopWatch.min * 1000 + stStopWatch.sec * 100 + stStopWatch.msec % 10);
	if (getButton1State()) // 버튼 1 눌린경우
	{
		setStopWatchState(eStopWatchRun); // 스톱워치 시작으로 상태 변경
	}
	else if (getButton2State()) // 버튼 2 눌린경우
	{
		setStopWatchState(eStopWatchReset); // 스톱워치 초기화
	}
}

void stopWatchRun() // 스톱워치 시작함수
{
	// FND로 데이터 출력하여 시작
	setFndData(stStopWatch.min * 1000 + stStopWatch.sec * 100 + stStopWatch.msec % 10);
	if (getButton1State()) // 버튼 1 눌린경우
	{
		setStopWatchState(eStopWatchStop); // 스톱워치 멈춤
	}
}

void stopWatchReset() // 스톱워치 리셋함수
{
	setTimeClock(&stStopWatch, 0, 0, 0, 0, 0); // 타임클럭 모두 0으로 초기화
	setFndData(0);							   // FND 출력 0으로 지정
	setStopWatchState(eStopWatchStop);         // 상태 스톱워치 정지 상태로 정의
}

void stopWatchExcute() // 스톱워치 실행 함수
{
	switch (stopWatchState)
	{
	case eStopWatchStop:
		stopWatchStop(); // 스톱워치 멈춤
		PORTD = 0x01;	 // FND 설정
		break;
	case eStopWatchRun:
		stopWatchRun(); // 스톱워치 실행
		PORTD = 0x08;
		break;
	case eStopWatchReset:
		stopWatchReset(); // 스톱워치 리셋
		PORTD = 0x80;
		break;
	}
}