## 🕹 회로구성
### ✓ ATmega128
버튼 입력 받아 타이머 시작, 타이머에서 카운트 한 숫자 FND로 출력하기 위해 숫자 데이터와 숫자 출력할 FND 자릿수 데이터 CMOD-A7으로 출력
### ✓ CMOD-A7
숫자 데이터와 자릿수 데이터 입력받아, 숫자에 해당하는 7-Segment Font 데이터로 Decoding 하여 FND로 출력, 자릿수 데이터 이용하여 해당하는 FND ON 신호 출력
### ✓ UART
UART 통신 이용하여 PC로 스톱워치 시작, 정지 동작시 메시지 출력(ATmega128), 
PC에서 Serial 통신 프로그램(ex. COM Port Master) 사용하여 메시지 확인
PC에서 UART로 RUN, STOP 메시지 ATmega128로 출력 시 스톱워치 작동, 멈춤 구현하여 양방향 통신 구현
### ✓ I2C
Real Time Clock인 DS3231의 시간 데이터를 I2C통신 이용해 ATmega128로 불러와 FND로 시간 출력
