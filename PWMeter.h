#ifndef _PWMETER_H_
#define _PWMETER_H_

// Puse width meter
// Thanks to
// http://startelc.com/AVR/Avr_18InpCapt.html
// https://gist.github.com/billroy/4032657

#include <stdint.h>

#define PWMETER_BUFF_SIZE	32 // pulse width data buffer size

// Puse width meter class
// Input: pin #8 (PB0/ICP1)
// * This class is just for atmega328P Arduinos (Arduino UNO, Arduino Pro Mini).
// * This class uses Timer1.
// * Therefore, it conflicts with Servo library, Timer1 library,
// * and PWM output of pin #3 and #11.
class PWMeter
{
public:
	void begin();			// begin the PWMeter
	bool available();		// new value available?
	uint16_t get();			// get a buffered value [usec]
	uint16_t getLast();		// get the last value [usec]
	
	void isr();				// input capture interrupt handler

private:
	uint8_t pulse_state;	// waiting for rising edge or falling edge?
	uint16_t cnt1;			// start time of pulse
	uint16_t cnt2;			// end time of pulse
	uint16_t buffer[PWMETER_BUFF_SIZE]; // pulse width data buffer (ring buffer)
	uint8_t rptr;			// read pointer of buffer
	uint8_t wptr;			// write pointer of buffer
};

#endif
