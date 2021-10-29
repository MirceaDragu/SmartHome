#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>
#include "DigitSegment.h"

#define SHCP PD5
#define STCP PD6
#define DS PD7

#define A 0b01111111
#define B 0b10111111
#define C 0b11011111
#define D 0b11101111
#define E 0b11110111
#define F 0b11111011
#define G 0b11111101
#define DP 0b11111110

void init()
{
	DDRD |= (1<<SHCP) | (1<<STCP) | (1<<DS) | (1<<PD4) | (1<<PD3);
	DDRA |= (1<<PA7) | (1<<PA6);
}

void SHCPpulse()
{
	PORTD &= ~(1<<SHCP);//0
	PORTD |= (1<<SHCP);//1
	PORTD &= ~(1<<SHCP);//0
}

void STCPpulse()
{
	PORTD &= ~(1<<STCP);//0
	//_delay_ms(1);
	PORTD |= (1<<STCP);//1
	//_delay_ms(1);
	PORTD &= ~(1<<STCP);//0
	//_delay_ms(1);
	
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
			//SHCPpulse();
			PORTD &= ~(1<<DS);
			SHCPpulse();
			
		}
		else
		{
			//SHCPpulse();
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