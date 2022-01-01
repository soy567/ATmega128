#include "Fnd.h"

void fndInit() {
    FND_COM_DDR |= (1 << FND_COM_01) | (1 << FND_COM_02) | (1 << FND_COM_03) | (1 << FND_COM_04);
    FND_DATA_DDR |= 0xff;
}

void fndDisplayData(uint16_t fndData) {
    static uint16_t displayState = 0;

    if (fndData >= 10000)
        fndData = 9999;
    else if (fndData < 0)
        fndData = 0;

    displayState = (displayState + 1) % 4;

    switch (displayState) {
        case 0:
            fndWriteData(FND_DIGIT_1, fndData / 1000);
            break;

        case 1:
            fndWriteData(FND_DIGIT_2, (fndData / 100) % 10);
            break;

        case 2:
            fndWriteData(FND_DIGIT_3, (fndData / 10) % 10);
            break;

        case 3:
            fndWriteData(FND_DIGIT_4, fndData % 10);
            break;
    }
}

void fndWriteData(uint8_t fndPosition, uint8_t fndData) {
    // fnd에 출력할 숫자에 따른 7-Segment font 정보
    uint8_t aFndFont[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};

    // 출력 데이터 범위 검사
    if (fndData >= 10)
        fndData = 0;
    else if (fndData < 0)
        fndData = 0;

    // 출력 위치 범위 검사
    if (fndPosition >= 4)
        fndPosition = 0;
    else if (fndPosition < 0)
        fndPosition = 0;
	
    FND_COM_PORT &= ~((1 << FND_COM_01) | (1 << FND_COM_02) | (1 << FND_COM_03) | (1 << FND_COM_04));
    FND_DATA_PORT = ~aFndFont[fndData];

	// 출력 위치 따라 COM Port에 High입력하여 해당 위치의 7-Segment on
    switch (fndPosition) {
        case FND_DIGIT_1:
            FND_COM_PORT |= (1 << FND_COM_01);
            break;

        case FND_DIGIT_2:
            FND_COM_PORT |= (1 << FND_COM_02);
            break;

        case FND_DIGIT_3:
            FND_COM_PORT |= (1 << FND_COM_03);
            break;

        case FND_DIGIT_4:
            FND_COM_PORT |= (1 << FND_COM_04);
            break;
    }
}