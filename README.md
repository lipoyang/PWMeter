# PWMeter
Pulse width meter class library for Arduiono UNO / Pro Mini

## Target
This class is just for atmega328P Arduinos (Arduino UNO, Arduino Pro Mini and so on)

## Input
The pulse input is fixed to the pin #8 (PB0/ICP1).

## Resolution
The measured value is 16 bits wide. LSB is equivalent to 1usec. Then, 0 to 65535 usec pulse width is supported.

## Notes
This class uses Timer1. Therefore, it conflicts with Servo library, Timer1 library, and PWM output of pin #3 and #11.  
***
# PWMeter (日本語)
Pulse width meter class library for Arduiono UNO / Pro Mini

## Target
This class is just for atmega328P Arduinos (Arduino UNO, Arduino Pro Mini and so on)

## Input
The pulse input is fixed to the pin #8 (PB0/ICP1).

## Resolution
The measured value is 16 bits wide. LSB is equivalent to 1usec. Then, 0 to 65535 usec pulse width is supported.

## Notes
This class uses Timer1. Therefore, it conflicts with Servo library, Timer1 library, and PWM output of pin #3 and #11.
