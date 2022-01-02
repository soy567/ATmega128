﻿#ifndef DS3231_H_
#define DS3231_H_

#include <avr/io.h>
#include "i2c.h"

#define DS3231_SLA	0x68 // dev 주소 정의
#define READ		1
#define WRITE		0
#define DS3231_SLA_READ		(0x68<<1 | READ)	// read payload 정의
#define DS3231_SLA_WRITE	(0x68<<1 | WRITE)	// write payload 정의

// DS3231 메모리 주소 지정
#define DS3231_ADDR_SEC			0x00
#define DS3231_ADDR_MIN			0x01
#define DS3231_ADDR_HOUR		0x02
#define DS3231_ADDR_DAYOFWEEK	0x03
#define DS3231_ADDR_DATE		0x04
#define DS3231_ADDR_MONTH		0x05
#define DS3231_ADDR_YEAR		0x06

// 사용할 구조체 자료형 정의
typedef struct ds3231_time {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;	
} DS3231_TIME;

typedef struct ds3231_date {
	uint8_t DayOfWeek;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} DS3231_DATE;


void DS3231_TxByte(uint8_t memAddr, uint8_t data);
void DS3231_RxByte(uint8_t memAddr, uint8_t *data);
void DS3231_WriteStream(uint8_t memAddr, uint8_t *data, uint8_t size);
void DS3231_ReadStream(uint8_t memAddr, uint8_t *data, uint8_t size);
void DS3231_InitTime(uint8_t year, uint8_t month, uint8_t date, uint8_t DOW,
						uint8_t hour, uint8_t min, uint8_t sec);
uint8_t BCDtoDEC(uint8_t bcd);
uint8_t DECtoBCD(uint8_t dec);
void DS3231Excute();


#endif /* DS3231_H_ */