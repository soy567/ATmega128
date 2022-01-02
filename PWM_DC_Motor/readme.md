## 🕹 회로구성
### ✓ ATmega128
버튼 입력 받아 선풍기 세기 조절
### ✓ I2C
Real Time Clock인 DS3231의 시간 데이터를 I2C통신 이용해 ATmega128로 출력
I2C 방식 LCD Display 연결하여 선풍기 세기와(Duty rate) DS3231에서 받아온 시간 출력
### ✓ PWM
선풍기 세기에 따라 PWM의 Duty rate 조절하여 DC Motor에 입력하여 DC Motor 세기 조절
