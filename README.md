# PWMeter
Pulse width meter class library for Arduiono UNO / Pro Mini

## Target
This class is just for ATmega328P Arduinos (Arduino UNO, Arduino Pro Mini and so on)

## Input
The pulse input is fixed to the pin #8 (PB0/ICP1).

## Resolution
LSB is equivalent to 1usec. 16MHz-clock board (like as Arduino UNO and Pro Mini(5V)) can measure 0 to 32767 usec pulse. 8MHz-clock board (like as Arduino Pro Mini(3.3V)) can measure 0 to 65535 usec pulse.

## Notes
This class uses Timer1. Therefore, it conflicts with Servo library, Timer1 library, and PWM output (analogWrite()) of pin #3 and #11.  

***
# PWMeter (日本語)
Arduiono UNO / Pro Mini用の、パルス幅計測クラスライブラリです。

## ターゲット
このクラスは、ATmega328P登載のArduino (Arduino UNO、Arduino Pro Miniなど) 専用です。

## 入力ピン
パルス入力は、#8ピン (PB0/ICP1) 固定です。

## 計測精度
最下位ビットが1usecに相当します。Arduino UNO や Pro Mini(5V)など16MHzクロックのボードでは、0～32767usecのパルスを計測できます。Arduino Pro Mini(3.3V)など8MHzクロックのボードでは、0～65535usecのパルスを計測できます。

## 注意点
このクラスはTimer1を使用しています。そのため、Servoライブラリ、Timer1ライブラリ、およびピン#3、#11のPWM出力(analogWrite())と競合します。
