#include "UltraSonic.h"

uint16_t ultraSonicTimer = 0;
int ultraSonicRxFlag = 0;

//1. triggering을 한다. Low -> High 10us유지-> Low
//US_PORT |= (1<<US_TRIG);
//_delay_us(10);
//2. 초음파 송신
//3. Echo pin high 변경,
//4. Int발생, timer=0, timer 스타트
//4. 초음파 수신
//5. Echo pin low 변경,
//6. Int발생, timer값 read
//7. timer 값을 거리로 변경

void US_getTimer() {
    ultraSonicTimer = TCNT1;
}

void US_EchoFallingEdge() {
    EICRA |= (1 << ISC01);   // falling edge
    EICRA &= ~(1 << ISC00);  // falling edge
}

void US_EchoRisingEdge() {
    EICRA |= (1 << ISC01) | (1 << ISC00);  // rising edge
}

void US_ClearTimer() {
    TCNT1 = 0;
}

void US_StartTimer() {
    TCCR1B |= (1 << CS11) | (1 << CS10);  // 16bit TCNT1 64분주비
}

void US_StopTimer() {
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));  // 16bit TCNT1 0분주비
}

void US_Init() {
    US_DDR |= (1 << US_TRIG);
    US_DDR &= ~(1 << US_ECHO);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01) | (1 << ISC00);  // rising edge

    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));  // 16bit TCNT1 0분주비
}

void US_Trigger() {
    US_PORT |= (1 << US_TRIG);
    _delay_us(10);
    US_PORT &= ~(1 << US_TRIG);
}

uint16_t US_Distance() {
    return (uint16_t)(0.068 * ultraSonicTimer);
}

int US_getRxFlag() {
    return ultraSonicRxFlag;
}

void US_ClearRxFlag() {
    ultraSonicRxFlag = 0;
}

void US_SetRxFlag() {
    ultraSonicRxFlag = 1;
}
