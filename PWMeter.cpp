#include <avr/interrupt.h>
#include <Arduino.h>
#include "PWMeter.h"

static PWMeter* s_meter = NULL;

// waiting for rising edge or falling edge?
enum{
	PULSE_RISING = 0,
	PULSE_FALLING
};

/*
 * Timer1 input capture interrupt handler (global)
 */
ISR(TIMER1_CAPT_vect)
{
	if(s_meter != NULL) s_meter->isr();
}

/*
 * Timer1 input capture interrupt handler
 */
void PWMeter::isr()
{
	byte sreg = SREG;			// backup the status register
	cli();						// disable interrupts
	
	// Timer1 input captuer interrupt flag clear
	TIFR1 = _BV(ICF1);
	
	// rising edge
	if( pulse_state == PULSE_RISING ){
		pulse_state = PULSE_FALLING;
		
		cnt1 = ICR1;		// start time of pulse
		TCCR1B &=~_BV(ICES1);		// wait for falling edge
	}
	// falling edge
	else{
		pulse_state = PULSE_RISING;
		
		cnt2 = ICR1;				// end time of pulse
		buffer[wptr] = cnt2 - cnt1;	// pulse width
		uint8_t temp = wptr;
		if(++temp >= PWMETER_BUFF_SIZE) temp = 0;
		if(temp != rptr) wptr = temp;
		TCCR1B |= _BV(ICES1);		// wait for rising edge
	}
	
	//sei();					// enable interrupts
	SREG = sreg;				// restore the status register
}

/*
 * begin the PWMeter
 */
void PWMeter::begin()
{
	s_meter = this;
	
	// initialize variables
	pulse_state = PULSE_RISING;
	rptr = 0;
	wptr = 0;
	
	// Input: pin #8 (PB0/ICP1)
	pinMode(8, INPUT);
	digitalWrite(8, 0);
	
	// Timer1 setting
	TCCR1A = 0;
	TCCR1B = _BV(ICES1) | _BV(CS11); // edge=rising, prescaler=1/8 (*)
	TCCR1C = 0;
	// (*) 8MHz / 8 = 1MHz (1usec), 16MHz / 8 = 2MHz (0.5usec)
	
	// Timer1 input captuer interrupt flag clear
	TIFR1 = _BV(ICF1);
	// Timer1 input captuer interrupt enable
	TIMSK1 |= _BV(ICIE1);
}

/*
 * new value available?
 */
bool PWMeter::available()
{
	byte sreg = SREG;			// backup the status register
	cli();						// disable interrupts
	
	bool ret = (rptr != wptr);
	
	//sei();					// enable interrupts
	SREG = sreg;				// restore the status register
	
	return ret;
}

/*
 * get a buffered value
 * return: pulse witdh[usec], or 0xFFFF if no data is available
 */
uint16_t PWMeter::get()
{
	uint16_t ret;
	
	byte sreg = SREG;			// backup the status register
	cli();						// disable interrupts
	
	if(rptr != wptr){
		ret = buffer[rptr];
		if(++rptr >= PWMETER_BUFF_SIZE) rptr = 0;
	}else{
		ret = 0xFFFF;
	}
	
	//sei();					// enable interrupts
	SREG = sreg;				// restore the status register
	
	// CPU clock = 16MHz or 8MHz?
	if(F_CPU == 16000000UL){
		ret /= 2; // 0.5usec count => 1usec count
	}
	
	return ret;
}

/*
 * get the last value [usec]
 * return: pulse witdh[usec], or 0xFFFF if no data is available
 */
uint16_t PWMeter::getLast()
{
	uint16_t ret;
	
	byte sreg = SREG;			// backup the status register
	cli();						// disable interrupts
	
	if(rptr != wptr){
		rptr = (wptr > 0) ? (wptr - 1) : (PWMETER_BUFF_SIZE - 1);
		ret = buffer[rptr];
		if(++rptr >= PWMETER_BUFF_SIZE) rptr = 0;
	}else{
		ret = 0xFFFF;
	}
	
	//sei();					// enable interrupts
	SREG = sreg;				// restore the status register
	
	// CPU clock = 16MHz or 8MHz?
	if(F_CPU == 16000000UL){
		ret /= 2; // 0.5usec count => 1usec count
	}
	
	return ret;
}
