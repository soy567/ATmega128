#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Button.h"
#include "i2c.h"
#include "I2C_LCD.h"
#include "dcMotor.h"
#include "DS3231.h"
#include "timeClock.h"


int main(void) {
	initMotor();
	I2C_Init();	
	LCD_Init();
	buttonInit();
	
    while (1) {
		motorExcute();
		timeClockExec();
    }
}

