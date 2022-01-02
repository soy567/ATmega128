#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_DDR		DDRB
#define I2C_SCL		PB0
#define I2C_SDA		PB1

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
uint8_t I2C_RxData_Ack();
uint8_t I2C_RxData_Nack();


#endif /* I2C_H_ */