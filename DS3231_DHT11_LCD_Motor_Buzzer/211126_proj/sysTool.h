/*
 * sysTool.h
 *
 * Created: 2021-01-26 오전 11:33:27
 *  Author: kccistc
 */ 


#ifndef SYSTOOL_H_
#define SYSTOOL_H_
#include <avr/io.h>

void timeTick_Init(void);
void incTimeTick(void);
uint32_t getTimeTick(void);
void clearTimeTick(void);
void setTimeTick(uint32_t Value);



#endif /* SYSTOOL_H_ */