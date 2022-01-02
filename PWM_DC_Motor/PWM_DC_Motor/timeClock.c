#include "timeClock.h"

DS3231_TIME dsTime;
DS3231_DATE dsDate;


void timeClock_ISR_Process() {
	static uint16_t msCount = 0;
	char buff[30];
	char month[3];
	msCount++;
	if (msCount >= 1000)
	{
		msCount = 0;
		DS3231_ReadStream(DS3231_ADDR_SEC, (uint8_t *)&dsTime, sizeof(dsTime));
		DS3231_ReadStream(DS3231_ADDR_DAYOFWEEK, (uint8_t *)&dsDate, sizeof(dsDate));
	
		switch(dsDate.month) {
			case 1 : strcpy(month, "Jan"); break;
			case 2 : strcpy(month, "Feb"); break;
			case 3 : strcpy(month, "Mar"); break;
			case 4 : strcpy(month, "Apr"); break;
			case 5 : strcpy(month, "May"); break;
			case 6 : strcpy(month, "Jun"); break;
			case 7 : strcpy(month, "Jul"); break;
			case 8 : strcpy(month, "Aug"); break;
			case 9 : strcpy(month, "Sep"); break;
			case 10 : strcpy(month, "Oct"); break;
			case 11 : strcpy(month, "Nov"); break;
			case 12 : strcpy(month, "Dec"); break;
			default : strcpy(month, "Nul"); break;
		}
		sprintf(buff, "%s %d %02d:%02d:%02d", month, dsDate.date, dsTime.hour, dsTime.min, dsTime.sec);
		LCD_WriteStringXY(0, 0, buff);
	}
}


void timeClockExec() {
	char buff[30];
	char month[3];
	DS3231_ReadStream(DS3231_ADDR_SEC, (uint8_t *)&dsTime, sizeof(dsTime));
	DS3231_ReadStream(DS3231_ADDR_DAYOFWEEK, (uint8_t *)&dsDate, sizeof(dsDate));
		
	switch(dsDate.month) {
		case 1 : strcpy(month, "Jan"); break;
		case 2 : strcpy(month, "Feb"); break;
		case 3 : strcpy(month, "Mar"); break;
		case 4 : strcpy(month, "Apr"); break;
		case 5 : strcpy(month, "May"); break;
		case 6 : strcpy(month, "Jun"); break;
		case 7 : strcpy(month, "Jul"); break;
		case 8 : strcpy(month, "Aug"); break;
		case 9 : strcpy(month, "Sep"); break;
		case 10 : strcpy(month, "Oct"); break;
		case 11 : strcpy(month, "Nov"); break;
		case 12 : strcpy(month, "Dec"); break;
		default : strcpy(month, "Nul"); break;
	}
	sprintf(buff, "%s %d %02d:%02d:%02d", month, dsDate.date, dsTime.hour, dsTime.min, dsTime.sec);
	LCD_WriteStringXY(0, 0, buff);
}
