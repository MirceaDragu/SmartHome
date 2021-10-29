#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>
#include "LCD.h"

void scrie_caracter(volatile uint8_t *portrse, volatile uint8_t *portout, char c, int rs, int enable)
{
	*portrse |= (1<<rs) | (1<<enable);
	*portout = c;
	_delay_ms(1);
	*portrse &= ~(1<<enable);
	
}

void alegepoz(volatile uint8_t *portrse, volatile uint8_t *portout, unsigned int poz, int rs, int enable)
{
	
	*portrse &= ~(1<<rs);
	*portrse |= (1<<enable);
	*portout = poz;
	_delay_ms(1);
	*portrse &= ~(1<<enable);
}

void scrie_text(volatile uint8_t *portrse, volatile uint8_t *portout, char *text, int rs, int enable)
{
	
	while(*text)
	{
		*portrse |= (1<<rs) | (1<<enable);
		*portout = (*text++);
		_delay_ms(1);
		*portrse &= ~(1<<enable);
	}
	
}

void initLCD(volatile uint8_t *portrse, volatile uint8_t *portout, int rs, int enable)
{
	int i;
	
	for(i=1; i<=4; i++)
	{
		*portrse &= ~(1<<rs);
		*portrse |= (1<<enable);
		*portout = 0x38;
		_delay_ms(5);
		*portrse &= ~(1<<enable);
	}
	
	*portrse &= ~(1<<rs);
	*portrse |= (1<<enable);
	*portout = 0x08;
	_delay_ms(5);
	*portrse &= ~(1<<enable);
	
	*portrse &= ~(1<<rs);
	*portrse |= (1<<enable);
	*portout = 0x01;
	_delay_ms(1);
	*portrse &= ~(1<<enable);
	
	*portrse &= ~(1<<rs);
	*portrse |= (1<<enable);
	*portout = 0x06;
	_delay_ms(1);
	*portrse &= ~(1<<enable);
	
	*portrse &= ~(1<<rs);
	*portrse |= (1<<enable);
	*portout = 0x0E;
	_delay_ms(1);
	*portrse &= ~(1<<enable);
	
}
