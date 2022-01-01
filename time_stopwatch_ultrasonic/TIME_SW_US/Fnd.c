#include "Fnd.h"

int fndValue = 0; // FND device의 속성값.

void setFndData(int data)
{
	if (data >= 10000)
		data = 9999;
	else if (data < 0)
		data = 0;

	fndValue = data;
}

int getFndData()
{
	return fndValue;
}

void fndISRProcess()
{
	fndDispayData(getFndData());
}

void fndInit()
{
	FND_COM_DDR |= (1 << FND_COM_D4) | (1 << FND_COM_D3) | (1 << FND_COM_D2) | (1 << FND_COM_D1);
	FND_DATA_DDR = 0xff;
}

void fndDispayData(uint16_t fndData)
{
	static uint8_t displayState = 0;

	if (fndData >= 10000)
		fndData = 9999;
	else if (fndData < 0)
		fndData = 0;

	displayState = (displayState + 1) % 4;

	switch (displayState)
	{
	case 0:
		fndWriteData(FND_DIGIT_1, fndData / 1000); // 천의 자리
		break;
	case 1:
		fndWriteData(FND_DIGIT_2, fndData / 100 % 10); // 백의 자리
		break;
	case 2:
		fndWriteData(FND_DIGIT_3, fndData / 10 % 10); // 십의 자리
		break;
	case 3:
		fndWriteData(FND_DIGIT_4, fndData % 10); // 일의 자리
		break;
	}
}

void fndWriteData(uint8_t fndPosition, uint8_t fndData)
{
	uint8_t aFndFont[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};

	if (fndData >= 10)
		fndData = 0;
	else if (fndData < 0)
		fndData = 0;

	if (fndPosition >= 4)
		fndPosition = 0;
	else if (fndPosition < 0)
		fndPosition = 0;

	FND_COM_PORT &= ~((1 << FND_COM_D4) | (1 << FND_COM_D3) | (1 << FND_COM_D2) | (1 << FND_COM_D1));
	FND_DATA_PORT = ~aFndFont[fndData];
	switch (fndPosition)
	{
	case FND_DIGIT_1:
		FND_COM_PORT |= (1 << FND_COM_D1); //천의 자리
		break;
	case FND_DIGIT_2:
		FND_COM_PORT |= (1 << FND_COM_D2); //백의 자리
		break;
	case FND_DIGIT_3:
		FND_COM_PORT |= (1 << FND_COM_D3); //십의 자리
		break;
	case FND_DIGIT_4:
		FND_COM_PORT |= (1 << FND_COM_D4); //일의 자리
		break;
	}
}
