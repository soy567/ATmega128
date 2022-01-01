#include "Fnd.h"

int fndValue = 0; // FND device의 속성값.

// FND 데이터 수정 함수
void setFndData(int data)
{
	if (data >= 10000)
		data = 9999; // 출력범위 초과한 경우 9999
	else if (data < 0)
		data = 0; // 입력 데이터 0보다 작은경우 0

	fndValue = data; // 입력받은 데이터 fndValue에 입력
}

// FND의 데이터 가져오기
int getFndData()
{
	return fndValue;
}

// 인터럽트 작동시 FND 처리함수
void fndISRProcess()
{
	fndDispayData(getFndData());
}

// FND 초기화 함수
void fndInit()
{
	FND_DATA_DDR = 0xff; // 출력으로 DDR 설정
	// 초기 출력값은 모두 1로 설정
	FND_COM_DDR |= (1 << FND_COM_D4) | (1 << FND_COM_D3) | (1 << FND_COM_D2) | (1 << FND_COM_D1);
}

// FND에 출력할 각 자릿수 데이터 계산하고 출력하는 함수
void fndDispayData(uint16_t fndData)
{
	static uint8_t displayState = 0; // 출력상태 저장할 변수

	// 데이터 범위 검사
	if (fndData >= 10000)
		fndData = 9999;
	else if (fndData < 0)
		fndData = 0;

	// 표시할 디스플레이의 자릿수 지정
	displayState = (displayState + 1) % 4;

	switch (displayState)
	{
	case 0:
		fndWriteData(FND_DIGIT_1, fndData / 1000); // 천의 자리 출력
		break;
	case 1:
		fndWriteData(FND_DIGIT_2, fndData / 100 % 10); // 백의 자리 출력
		break;
	case 2:
		fndWriteData(FND_DIGIT_3, fndData / 10 % 10); // 십의 자리
		break;
	case 3:
		fndWriteData(FND_DIGIT_4, fndData % 10); // 일의 자리
		break;
	}
}

// FND에 데이터 쓰기 함수
void fndWriteData(uint8_t fndPosition, uint8_t fndData)
{
	// FND의 폰트 정의 (0~9, 각각이 7seg에서 불을 켤 LED를 나타냄)
	uint8_t aFndFont[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};

	// 각 자릿수 데이터 범위 검사
	if (fndData >= 10)
		fndData = 0;
	else if (fndData < 0)
		fndData = 0;

	// 각 자릿수 위치 데이터 범위 검사
	if (fndPosition >= 4)
		fndPosition = 0;
	else if (fndPosition < 0)
		fndPosition = 0;

	// COM포트의 값 0으로 초기화
	FND_COM_PORT &= ~((1 << FND_COM_D4) | (1 << FND_COM_D3) | (1 << FND_COM_D2) | (1 << FND_COM_D1));
	// Data Port에 fndData에 해당하는 숫자 Font 데이터 입력 (Common Anode 이므로 비트 반전)
	FND_DATA_PORT = ~aFndFont[fndData];

	switch (fndPosition)
	{
	case FND_DIGIT_1:
		FND_COM_PORT |= (1 << FND_COM_D1); //천의 자리 Seg 활성화
		break;
	case FND_DIGIT_2:
		FND_COM_PORT |= (1 << FND_COM_D2); //백의 자리 Seg 활성화
		break;
	case FND_DIGIT_3:
		FND_COM_PORT |= (1 << FND_COM_D3); //십의 자리 Seg 활성화
		break;
	case FND_DIGIT_4:
		FND_COM_PORT |= (1 << FND_COM_D4); //일의 자리 Seg 활성화
		break;
	}
}
