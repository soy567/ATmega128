#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "Button.h"
#include "DS3231.h"
#include "fndController_v1.h"
#include "i2c.h"
#include "led.h"
#include "stopWatch.h"
#include "uart0.h"
#include "uartQueue.h"

enum { TimeClock,
       StopWatch };

#endif /* MAIN_H_ */