#include "DS3231.h"

#include <avr/delay.h>

#include "fndController_v1.h"

DS3231_TIME dsTime;
DS3231_DATE dsDate;

void DS3231_TxByte(uint8_t memAddr, uint8_t data) {
    I2C_Start();                   // Start 신호 전송
    I2C_TxData(DS3231_SLA_WRITE);  // DS3231 dev 주소 전송
    I2C_TxData(memAddr);           // DS3231의 내부 메모리 주소 전송
    I2C_TxData(DECtoBCD(data));    // 내부 메모리 주소에 데이터 write
    I2C_Stop();                    // stop 신호 전송
}

void DS3231_RxByte(uint8_t memAddr, uint8_t *data) {
    I2C_Start();                          // Start 신호 전송
    I2C_TxData(DS3231_SLA_WRITE);         // DS3231 dev 주소 전송
    I2C_TxData(memAddr);                  // DS3231의 내부 메모리 주소 전송
    I2C_Start();                          // Repeat Start 신호 전송
    I2C_TxData(DS3231_SLA_READ);          // DS3231 dev 주소 + read 전송
    *data = BCDtoDEC(I2C_RxData_Nack());  // DS3231 메모리 주소 값 1byte를 수신
    I2C_Stop();                           // stop 신호 전송
}

void DS3231_WriteStream(uint8_t memAddr, uint8_t *data, uint8_t size) {
    I2C_Start();                   // Start 신호 전송
    I2C_TxData(DS3231_SLA_WRITE);  // DS3231 dev 주소 전송
    I2C_TxData(memAddr);           // DS3231의 내부 메모리 주소 전송
    // 내부 메모리 주소에 데이터 write (스트림 사이즈 만큼 반복하여 전송)
    for (int i = 0; i < size; i++)
        I2C_TxData(DECtoBCD(data[i]));
    I2C_Stop();  // stop 신호 전송
}

void DS3231_ReadStream(uint8_t memAddr, uint8_t *data, uint8_t size) {
    I2C_Start();                   // Start 신호 전송
    I2C_TxData(DS3231_SLA_WRITE);  // DS3231 dev 주소 전송
    I2C_TxData(memAddr);           // DS3231의 내부 메모리 주소 전송
    I2C_Start();                   // Repeat Start 신호 전송
    I2C_TxData(DS3231_SLA_READ);   // DS3231 dev 주소 + read 전송
    // DS3231 메모리 주소 값 1byte를 수신 (스트림 사이즈보다 하나 작은 부분가지는 Ack 전송하여 읽음)
    for (int i = 0; i < size - 1; i++)
        data[i] = BCDtoDEC(I2C_RxData_Ack());
    data[size - 1] = BCDtoDEC(I2C_RxData_Nack());  // 마지막 스트림 수신후 Nack 보내 수신 종료
    I2C_Stop();                                    // stop 신호 전송
}

// DS3231의 시간 직접 입력하여 초기화 하기 위한 함수
void DS3231_InitTime(uint8_t year, uint8_t month, uint8_t date, uint8_t DOW,
                     uint8_t hour, uint8_t min, uint8_t sec) {
    DS3231_DATE dsDate = {year, month, date, DOW};
    DS3231_DATE dsTime = {hour, min, sec};

    DS3231_WriteStream(DS3231_ADDR_DOW, (uint8_t *)&dsDate, sizeof(dsDate));
    DS3231_WriteStream(DS3231_ADDR_SEC, (uint8_t *)&dsTime, sizeof(dsTime));
}

uint8_t BCDtoDEC(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0f);
}

uint8_t DECtoBCD(uint8_t dec) {
    return (((dec / 10) << 4) | (dec % 10));
}

void DS3231Excute() {
    DS3231_ReadStream(DS3231_ADDR_SEC, (uint8_t *)&dsTime, sizeof(dsTime));
    DS3231_ReadStream(DS3231_ADDR_DAYOFWEEK, (uint8_t *)&dsDate, sizeof(dsDate));
    printf("%02d:%02d:%02d \n", dsDate.year, dsDate.month, dsDate.date);
    printf("%02d:%02d:%02d \n", dsTime.hour, dsTime.min, dsTime.sec);
    fnd_writeData(dsTime.min * 100 + dsTime.sec);
    _delay_ms(1000);
}