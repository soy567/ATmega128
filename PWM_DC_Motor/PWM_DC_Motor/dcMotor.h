#ifndef DCMOTOR_H_
#define DCMOTOR_H_


#include <avr/io.h>
#include <stdio.h>
#include "Button.h"
#include "I2C_LCD.h"

void initMotor();
void motorExcute();

#endif /* DCMOTOR_H_ */