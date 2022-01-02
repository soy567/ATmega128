﻿/*
 * sysTool.c
 *
 * Created: 2021-01-26 오전 11:33:11
 *  Author: kccistc
 */ 

#include "sysTool.h"

volatile uint32_t timeTick = 0;

void timeTick_Init(void)
{
	//timer0, 64분주, ctc mode
	TCCR0 |= (1<<WGM01); // CTC Mode
	TCCR0 |= (1<<CS02); // 64분주비
	TIMSK |= (1<<OCIE0); // OC Interrupt Mask 
	OCR0 = 250-1; // 1ms
}

void incTimeTick(void)
{
	timeTick++;
}

uint32_t getTimeTick(void)
{
	return timeTick;
}

void clearTimeTick(void)
{
	timeTick = 0;
}

void setTimeTick(uint32_t Value)
{
	timeTick = Value;
}