#ifndef FND_H_
#define FND_H_

#include <avr/io.h>

// FND com 포트로 PORTE 사용 (4~7, 각 Seg 제어용)
#define FND_COM_DDR DDRE
#define FND_COM_PORT PORTE
#define FND_COM_D1 4
#define FND_COM_D2 5
#define FND_COM_D3 6
#define FND_COM_D4 7

// Digit Data 포트로 PORTF 사용(0~3)
#define FND_DATA_DDR DDRF
#define FND_DATA_PORT PORTF

#define FND_DIGIT_1 0
#define FND_DIGIT_2 1
#define FND_DIGIT_3 2
#define FND_DIGIT_4 3

// FND 제어함수 헤더 정의
void fndInit();
void fndDispayData(uint16_t fndData);
void fndWriteData(uint8_t fndPosition, uint8_t fndData);
void setFndData(int data);
int getFndData();
void fndISRProcess();

#endif /* FND_H_ */