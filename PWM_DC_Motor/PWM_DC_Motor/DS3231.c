﻿#include "DS3231.h"

DS3231_TIME dsTime;
DS3231_DATE dsDate;


void DS3231_TxByte(uint8_t memAddr, uint8_t data)
{
	// 1. Start 신호 전송
	I2C_Start();
	// 2. DS3231 dev 주소 전송
	I2C_TxData(DS3231_SLA_WRITE);
	// 3. DS3231의 내부 메모리 주소 전송
	I2C_TxData(memAddr);
	// 4. 내부 메모리 주소에 데이터 write
	I2C_TxData(DECtoBCD(data));
	// 5. stop 신호 전송
	I2C_Stop();
}

void DS3231_RxByte(uint8_t memAddr, uint8_t *data)
{
	// 1. Start 신호 전송
	I2C_Start();
	// 2. DS3231 dev 주소 전송
	I2C_TxData(DS3231_SLA_WRITE);
	// 3. DS3231의 내부 메모리 주소 전송
	I2C_TxData(memAddr);
	// 4. repeat Start 신호 전송
	I2C_Start();
	// 5. DS3231 Dev 주소 + read 전송
	I2C_TxData(DS3231_SLA_READ);
	// 6. DS3231 메모리 주소 값 1byte를 수신
	*data = BCDtoDEC(I2C_RxData_Nack());
	// 7. stop 신호 전송
	I2C_Stop();
}

void DS3231_WriteStream(uint8_t memAddr, uint8_t *data, uint8_t size)
{
	// 1. Start 신호 전송
	I2C_Start();
	// 2. DS3231 dev 주소 전송
	I2C_TxData(DS3231_SLA_WRITE);
	// 3. DS3231의 내부 메모리 주소 전송
	I2C_TxData(memAddr);
	// 4. 내부 메모리 주소에 size 크기 바이트 데이터 write
	for (int i=0; i<size; i++)
	{
		I2C_TxData(DECtoBCD(data[i]));
	}
	// 5. stop 신호 전송
	I2C_Stop();
}

void DS3231_ReadStream(uint8_t memAddr, uint8_t *data, uint8_t size)
{
	// 1. Start 신호 전송
	I2C_Start();
	// 2. DS3231 dev 주소 전송
	I2C_TxData(DS3231_SLA_WRITE);
	// 3. DS3231의 내부 메모리 주소 전송
	I2C_TxData(memAddr);
	// 4. repeat Start 신호 전송
	I2C_Start();
	// 5. DS3231 Dev 주소 + read 전송
	I2C_TxData(DS3231_SLA_READ);
	// 6. DS3231 메모리 주소 값 1byte를 수신
	for (int i=0; i<size-1; i++)
	{
		data[i] = BCDtoDEC(I2C_RxData_Ack());
	}
	data[size-1] = BCDtoDEC(I2C_RxData_Nack());
	
	// 7. stop 신호 전송
	I2C_Stop();
}

uint8_t BCDtoDEC(uint8_t bcd) {
	return (bcd>>4) * 10 + (bcd & 0x0f);
}

uint8_t DECtoBCD(uint8_t dec) {
	return (((dec/10)<<4) | (dec%10));
}