#include "main.h"

ISR (TIMER0_COMP_vect) {
	incTimeTick();
}

int main(void)
{
	initMotor();
	I2C_Init();
	LCD_Init();
	DHT11_Init();
	buttonInit();
	BuzzerInit();
	timeTick_Init();
	
	sei();
	
	motorExcute();
	DHT11_Exec();
	
	uint32_t prevTime = 0;
	
	while (1) {
		if(getButton1State()) {
			BuzzerButton1();	
			motorExcute();
		}
		else if(getTimeTick() - prevTime > 2000) {
			prevTime = getTimeTick();
			DHT11_Exec();
		}
		timeClockExec();
	}
}

