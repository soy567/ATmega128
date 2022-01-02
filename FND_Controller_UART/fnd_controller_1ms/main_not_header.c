// main.h 분리하지 않은 main 파일
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Button.h"
#include "fnd_controller_v1.h"

enum { STOP,
       RUN,
       RESET };  // STOP -> 1, RUN ->2 ...
enum { FND_ON,
       FND_OFF };

ISR(TIMER0_OVF_vect) {
    fnd_ISR_Process();
}

int main(void) {
    fnd_init();

    // timer0 Interrupt 설정
    TCCR0 |= (1 << CS02);   // prescaler 분주비 64로 설정
    TIMSK |= (1 << TOIE0);  // timer 0의 오버플로우 인터럽트 활성화

    sei();  // global inturrupt 실행명령
    fnd_enable();
    uint16_t fnd_value = 0;
    uint8_t state = STOP;
    uint8_t fnd_blight_state = FND_ON;

    while (1) {
        // Event 처리 code
        switch (fnd_blight_state) {
            case FND_ON:
                if (getButton3State()) fnd_blight_state = FND_OFF;
                break;
            case FND_OFF:
                if (getButton3State()) fnd_blight_state = FND_ON;
                break;
        }

        switch (state) {
            case STOP:
                if (getButton1State())
                    state = RUN;  // run state
                else if (getButton2State())
                    state = RESET;  // reset state
                break;
            case RUN:
                if (getButton1State()) state = STOP;
                break;
            case RESET:
                state = STOP;
                break;
        }

        // 실행 code
        switch (fnd_blight_state) {
            case FND_ON:
                fnd_enable();
            case FND_OFF:
                fnd_disable();
        }
        switch (state) {
            case STOP:
                break;  // stop state

            case RUN:
                fnd_writeData(fnd_value);
                _delay_ms(100);
                fnd_value++;
                if (fnd_value >= 10000) fnd_value = 0;
                break;  // run state

            case RESET:
                fnd_value = 0;
                fnd_writeData(fnd_value);
                break;  // reset state
        }
    }
}
