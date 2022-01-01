#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_DDR DDRC // 버튼 사용할 DDR(Data Direction Register) 정의
#define BUTTON_PIN PINC // 버튼 출력신호 입력받을 핀 설정
#define BUTTON1 0       // 1번 버튼 받을 인풋 번호
#define BUTTON2 1       // 2번 버튼 받을 인풋 번호
#define BUTTON3 2       // 3번 버튼 받을 인풋 번호

#define RELEASED 1 // 버튼 눌리지 않았을 때 논리값 정의
#define PUSHED 0   // 버튼 눌렸을 때 논리값 정의
#define TRUE 1
#define FALSE 0

// 버튼에서 사용할 함수 헤더 정의
void buttonInit();
uint8_t getButton1State();
uint8_t getButton2State();
uint8_t getButton3State();

#endif /* BUTTON_H_ */