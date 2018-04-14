#include "PWMeter.h"

PWMeter pwmeter;

void setup()
{
	Serial.begin(19200);
	analogWrite(3, 0);
	pwmeter.begin();
}

void loop()
{
	static uint8_t duty = 0;
	uint16_t pw;
	
	analogWrite(3,duty);
	duty++;
	
	if(pwmeter.available()){
		uint16_t pw = pwmeter.getLast();
		Serial.println(pw);
	}
	delay(100);
}

