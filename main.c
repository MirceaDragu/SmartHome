/*
 * SmartHome.c
 *
 * Created: 7/12/2021 6:26:07 PM
 * Author : Mircea
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"
#include "DigitSegment.h"
#include "ADC.h"

#define RS PA0
#define ENABLE PA1
#define LED_GREEN PD2
#define LED_RED PA3
#define ADCe PA2

volatile uint8_t my_count=0;
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 5;
	my_count++;
	if(my_count >= 30)
	{
		
		TimeCalcul();
		my_count=0;
		
	}
	afisare();
	
}

int main(void)
{
	char text[]="Smart Home";
	DDRA |= (1<<RS) | (1<<ENABLE) | (1<<LED_RED) | (1<<PA4);
	DDRA &= ~(1<<ADCe);
	DDRC = 0xFF;
	DDRD |= (1<<LED_GREEN);
	PORTA = 0xFF;
	PORTD = 0xFF;
	PORTC = 0xFF;
	PORTA &= ~(1<<PA6) & ~(1<<PA7) & ~(1<<PA4);
	PORTD &= ~(1<<PD3) & ~(1<<PD4);
	DDRD = DDRD | ( 1<<PD1) ;
	DDRD = DDRD & ~(1<<PD0) ;
	
	sei();
	init_timer();
	init();
	initADC();
	initLCD(&PORTA, &PORTC, RS, ENABLE);
	alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
	scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
    while (1) 
    {
		
	}
}

