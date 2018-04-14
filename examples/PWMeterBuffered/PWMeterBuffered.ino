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
	delay(40);
	analogWrite(3,0);
	
	while((pw = pwmeter.get()) != 0xFFFF){
		Serial.print(pw);
		Serial.print("\t");
	}
	Serial.print("\n");
	delay(100);
}

