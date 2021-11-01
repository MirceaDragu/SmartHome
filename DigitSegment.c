#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "DigitSegment.h"
#include "ADC.h"
#include "LCD.h"

#define RS PA0
#define ENABLE PA1
#define SHCP PD5
#define STCP PD6
#define DS PD7
#define LED_GREEN PD2
#define LED_RED PA3

#define A 0b01111111
#define B 0b10111111
#define C 0b11011111
#define D 0b11101111
#define E 0b11110111
#define F 0b11111011
#define G 0b11111101
#define DP 0b11111110

int hxmm=0;
int xhmm=0;
int hhxm=0;
int hhmx=0;
int minut=0;
int hhmm;
int *a=0;
int size=3;

void init()
{
	DDRD |= (1<<SHCP) | (1<<STCP) | (1<<DS) | (1<<PD4) | (1<<PD3) | (1<<LED_GREEN);
	DDRA |= (1<<PA7) | (1<<PA6) | (1<<LED_RED) ;
}

void SHCPpulse()
{
	PORTD &= ~(1<<SHCP);
	PORTD |= (1<<SHCP);
	PORTD &= ~(1<<SHCP);
}

void STCPpulse()
{
	PORTD &= ~(1<<STCP);
	PORTD |= (1<<STCP);
	PORTD &= ~(1<<STCP);
}


void BitCalcul(uint8_t k)
{
	int bit;
	int i;
	for(i=0; i<8; i++)
	
	{
		bit=k%2;
		k=k/2;
		if(bit==0)
		{
			PORTD &= ~(1<<DS);
			SHCPpulse();
			
		}
		else
		{
			PORTD |= (1<<DS);
			SHCPpulse();
		}
		
	}
}

void Point()
{
	uint8_t v;
	v=DP;
	BitCalcul(v);
	STCPpulse();
}

void Write(uint8_t nr)
{
	uint8_t v;
	if(nr==1)
	{
		v=B&C;
		BitCalcul(v);
	}
	
	if(nr==2)
	{
		v=A&B&D&E&G;
		BitCalcul(v);
	}
	
	if(nr==3)
	{
		v=A&B&C&D&G;
		BitCalcul(v);
	}
	
	if(nr==4)
	{
		v=F&G&C&B;
		BitCalcul(v);
	}
	
	if(nr==5)
	{
		v=A&F&G&C&D;
		BitCalcul(v);
	}
	if(nr==6)
	{
		v=F&E&G&C&D&A;
		BitCalcul(v);
	}
	
	if(nr==7)
	{
		v=A&B&C;
		BitCalcul(v);
	}
	
	if(nr==8)
	{
		v=A&B&C&D&E&F&G;
		BitCalcul(v);
	}
	
	if(nr==9)
	{
		v=A&B&G&F&C&D;
		BitCalcul(v);
	}
	
	if(nr==0)
	{
		v=A&B&C&D&E&F;
		BitCalcul(v);
	}
	
	
	STCPpulse();
	
	
}

void TimeCalcul()
{
	
	char text[]="Smart Home";
	a=(int*)malloc(size*sizeof(int));
	if((PIND & (1<<PD0)) == 0 )
	{
		//PORTD = PORTD &  ~( 1<<PD1);
		hhxm=hhmx=hxmm=xhmm=0;
		clearL2();
		alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
		scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
		alegepoz(&PORTA,&PORTC,0xC5,RS,ENABLE);
		scrie_text(&PORTA, &PORTC,"INCHIS",RS,ENABLE);
		PORTA &= ~(1<<LED_RED); //aprindem bec rosu
		PORTD |= (1<<LED_GREEN); //stingem bec verde
	}
else
{
	hhmx++;
	if(minut == 59 )
	{
		hhxm = 0;
		hhmx = 0;
		hxmm++;
	}
	
	if(hhmx==10)
	{
		hhmx=0;
		hhxm++;
	}
	
	if(hxmm > 9)
	{
		hxmm = 0;
		xhmm++;
	}
	
	if((hxmm==3) && (xhmm==2) && (hhxm == 5) && (hhmx==9))
	{
		hxmm=xhmm=hhxm=hhmx=0;
	}
	minut = hhxm*10 +hhmx;
	hhmm = xhmm*1000 + hxmm*100 + hhxm*10 +hhmx;
		if( hhmm < 10) //if(hhmm <=600 || hhmm>=2200)
		{
			clearL2();
			alegepoz(&PORTA, &PORTC, 0x84, RS, ENABLE);
			scrie_text(&PORTA, &PORTC, text, RS, ENABLE);
			alegepoz(&PORTA,&PORTC,0xC5,RS,ENABLE);
			scrie_text(&PORTA, &PORTC,"INCHIS",RS,ENABLE);
			PORTA &= ~(1<<LED_RED); //aprindem bec rosu
			PORTD |= (1<<LED_GREEN); //stingem bec verde
			
			
		}
		else
		{
			clearL1();
			alegepoz(&PORTA,&PORTC,0xC5,RS,ENABLE);
			scrie_text(&PORTA, &PORTC,"DESCHIS",RS,ENABLE);
			PORTD &= ~(1<<LED_GREEN); //aprindem bec verde
			PORTA |= (1<<LED_RED); //stingem bec rosu
			WriteTemperature(size,a);
		}

}
		
}

void afisare()
{
	PORTD &= ~(1<<PD4);
	Write(hxmm);
	_delay_ms(5);
	Point();
	_delay_ms(5);
	PORTD |= (1<<PD4);
	
	PORTD &= ~(1<<PD3);
	Write(xhmm);
	_delay_ms(5);
	PORTD |= (1<<PD3);
	
	PORTA &= ~(1<<PA7);
	Write(hhxm);
	_delay_ms(5);
	PORTA |= (1<<PA7);
	
	//_delay_ms(1000);
	PORTA &= ~(1<<PA6);
	Write(hhmx);
	_delay_ms(5);
	//_delay_ms(10);
	PORTA |= (1<<PA6);
}

void init_timer()
{
	
	TCNT0 = 5;
	TIMSK |= (1<<TOIE0);
	TCCR0 |= (1<<CS02); 
}