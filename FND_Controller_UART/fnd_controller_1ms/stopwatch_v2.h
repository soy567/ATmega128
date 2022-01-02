#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "Button.h"
#include "fnd_controller_v1.h"
#include "uartQueue.h"


enum {STOP, RUN, RESET}; // STOP -> 1, RUN ->2 ...
enum {FND_ON, FND_OFF};

struct _time {
	uint8_t ms;
	uint8_t hms;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
};

void stopWatchInit();
void stopWatch_ISR_Process();
void stopWatchExcute();

#endif /* STOPWATCH_H_ */