/*
 * SmartHome.c
 *
 * Created: 7/12/2021 6:26:07 PM
 * Author : Mircea
 */ 

#include <avr/io.h>
#define F_CPU 16000000
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
	uint8_t min2=0;
	uint8_t min1 =0;
	uint8_t ora2 =0;
	uint8_t ora1 =0;
	uint16_t var =0;
	uint16_t hour;
	uint8_t *a=0;
	uint8_t size=3;
	a=(uint8_t*)malloc(size*sizeof(uint8_t));
	initADC();
	init();
	initLCD(&PORTA, &PORTC, RS, ENABLE);
	//alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
	//scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
    while (1) 
    {
		//alegepoz(&PORTA, &PORTC, 0x80, RS, ENABLE);
		//scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
		//WriteTemperature(3,a);
		if(min1 == 6)
		{
			min1 = 0;
			min2 = 0;
			ora1++;
		}
		
		if(min2==10)
		{
			min2=0;
			min1++;
		}
		
		if(ora1 > 9)
		{
			ora1 = 0;
			ora2++;
		}
		
		if((ora1==3) && (ora2==2) && (min1 == 5) && (min2==9))
		{
			ora1=ora2=min1=min2=0;
		}
		
		hour = ora2*1000 + ora1*100 + min1*10 +min2;//2000+300+50+9==2359
		
		if( hour <= 5) //|| hour>=2200)//interval 22:00 - 06:00
		{
			alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
			scrie_text(&PORTA, &PORTC,"                      ",RS,ENABLE);
			alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
			scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
			alegepoz(&PORTA,&PORTC,0xC5,RS,ENABLE);
			scrie_text(&PORTA, &PORTC,"INCHIS",RS,ENABLE);
			PORTA &= ~(1<<LED_RED); //aprindem bec rosu
			PORTD |= (1<<LED_GREEN); //stingem bec verde
				
		}
		else
		{
			
			alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
			scrie_text(&PORTA, &PORTC,"                      ",RS,ENABLE);
			alegepoz(&PORTA,&PORTC,0xC5,RS,ENABLE);
			scrie_text(&PORTA, &PORTC,"DESCHIS",RS,ENABLE);
			PORTD &= ~(1<<LED_GREEN); //aprindem bec verde
			PORTA |= (1<<LED_RED); //stingem bec rosu
			WriteTemperature(3,a);
			
		}
		
		PORTD &= ~(1<<PD4);
		Write(ora1);
		_delay_ms(10);
		var+=10;
		Point();
		_delay_ms(10);
		var+=10;
		PORTD |= (1<<PD4);
		
		PORTD &= ~(1<<PD3);
		Write(ora2);
		_delay_ms(10);
		var+=10;
		PORTD |= (1<<PD3);
		
		PORTA &= ~(1<<PA7);
		Write(min1);
		_delay_ms(10);
		var+=10;
		PORTA |= (1<<PA7);
		
		//_delay_ms(1000);
		PORTA &= ~(1<<PA6);
		if(var==1000)
		{
			min2++;
			var=0;
		}
		Write(min2);
		_delay_ms(1);
		PORTA |= (1<<PA6);
		
    }
}

