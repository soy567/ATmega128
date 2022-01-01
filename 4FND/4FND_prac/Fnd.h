#ifndef FND_H_
#define FND_H_

#include <avr/io.h>

#define FND_COM_DDR		DDRE
#define FND_COM_PORT	PORTE
#define FND_COM_01		4
#define FND_COM_02		5
#define FND_COM_03		6
#define FND_COM_04		7

#define FND_DATA_DDR	DDRF
#define FND_DATA_PORT	PORTF

#define FND_DIGIT_1		0
#define FND_DIGIT_2		1
#define FND_DIGIT_3		2
#define FND_DIGIT_4		3

void fndWriteData(uint8_t fndPosition, uint8_t fndData);
void fndDisplayData(uint16_t fndData);
void fndInit();

#endif /* FND_H_ */