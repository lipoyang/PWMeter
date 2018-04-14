# PWMeter
Pulse width meter class library for Arduiono UNO / Pro Mini

## Target
This class is just for ATmega328P Arduinos (Arduino UNO, Arduino Pro Mini and so on)

## Input
The pulse input is fixed to the pin #8 (PB0/ICP1).

## Resolution
The measured value is 16 bits wide. LSB is equivalent to 1usec. Then, 0 to 65535 usec pulse width is supported.

## Notes
This class uses Timer1. Therefore, it conflicts with Servo library, Timer1 library, and PWM output of pin #3 and #11.  

***
# PWMeter (日本語)
Arduiono UNO / Pro Mini用の、パルス幅計測クラスライブラリです。

## ターゲット
このクラスは、ATmega328P登載のArduino (Arduino UNO、Arduino Pro Miniなど) 専用です。

## 入力
パルス入力は、#8ピン (PB0/ICP1) 固定です。

## 測定精度
計測値は16ビットです。最下位ビットが1usecに相当します。つまり、0～65535usecのパルス幅に対応しています。

## 注意点
このクラスはTimer1を使用しています。そのため、Servoライブラリ、Timer1ライブラリ、およびピン#3、#11のPWM出力と競合します。
