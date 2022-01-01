#include "Button.h"

//버튼 초기화 코드 (초기값 모두 0으로 초기화)
void buttonInit()
{
	BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3));
}

// 버튼 상태(True or False) 가져오는 코드
uint8_t getButton1State()
{
	// 정적변수 Static -> 함수 종료되어도 프로그램 종료시 까지 값 유지됨
	static uint8_t prevButton1State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON1);

	if (prevButton1State != PUSHED && curButtonState == PUSHED)
	{
		//_delay_ms(50); // charttering SW적으로 제거하기 위한 코드
		prevButton1State = PUSHED;
		return FALSE;
	}
	else if (prevButton1State == PUSHED && curButtonState != PUSHED)
	{
		//_delay_ms(50);
		prevButton1State = RELEASED;
		return TRUE;
	}
	return FALSE; // 변화없는 상황일 경우 항상 FALSE
}

uint8_t getButton2State()
{
	static uint8_t prevButton2State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON2);

	if (prevButton2State != PUSHED && curButtonState == PUSHED)
	{
		//_delay_ms(50);
		prevButton2State = PUSHED;
		return FALSE;
	}
	else if (prevButton2State == PUSHED && curButtonState != PUSHED)
	{
		//_delay_ms(50);
		prevButton2State = RELEASED;
		return TRUE;
	}
	return FALSE;
}

uint8_t getButton3State()
{
	static uint8_t prevButton3State = RELEASED;
	uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON3);

	if (prevButton3State != PUSHED && curButtonState == PUSHED)
	{
		//_delay_ms(50);
		prevButton3State = PUSHED;
		return FALSE;
	}
	else if (prevButton3State == PUSHED && curButtonState != PUSHED)
	{
		//_delay_ms(50);
		prevButton3State = RELEASED;
		return TRUE;
	}
	return FALSE;
}
