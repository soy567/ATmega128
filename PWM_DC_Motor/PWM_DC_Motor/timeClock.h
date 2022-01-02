#ifndef TIMECLOCK_H_
#define TIMECLOCK_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "DS3231.h"
#include "I2C_LCD.h"

void timeClock_ISR_Process();
void timeClockExec();

#endif /* TIMECLOCK_H_ */