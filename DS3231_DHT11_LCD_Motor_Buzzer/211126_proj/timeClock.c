#include "timeClock.h"

DS3231_TIME dsTime;
DS3231_DATE dsDate;

char month[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void timeClockExec() {
	char buff[30];
	DS3231_ReadStream(DS3231_ADDR_SEC, (uint8_t *)&dsTime, sizeof(dsTime));
	DS3231_ReadStream(DS3231_ADDR_DAYOFWEEK, (uint8_t *)&dsDate, sizeof(dsDate));
	
	sprintf(buff, "%s %d %02d:%02d:%02d", month[dsDate.month-1], dsDate.date, dsTime.hour, dsTime.min, dsTime.sec);
	LCD_WriteStringXY(0, 0, buff);
}
