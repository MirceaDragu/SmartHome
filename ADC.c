#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>
#include "ADC.h"
#include "LCD.h"

#define BUZZ PA4

void initADC()
{
	ADMUX |= (1<<REFS0) | (1<<MUX1);
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
}

uint16_t readADC(uint8_t pin)
{
	ADMUX &= 0xE0;
	ADMUX |=pin;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
	
	
}

void WriteTemperature(uint8_t size, volatile uint8_t *a)
{
	uint16_t ADC_value;
	uint16_t ToWriteValue =0;
	int i;
	
	ADC_value = readADC(2);
	if(ADC_value > (1024 *4.89)/5)
	ToWriteValue = ((uint32_t)(3200));
	else
	if(ADC_value >=(1024*4)/5 && ADC_value < (1024*4.89)/5)
	ToWriteValue = ((uint32_t)(3100));
	else
	if(ADC_value >=(1024*3)/5 && ADC_value < (1024*4)/5)
	ToWriteValue = ((uint32_t)(3000));
	else
	ToWriteValue = (((uint32_t)(ADC_value *5)*100)/1024) * 10;
	
	if(ToWriteValue > 2700)
	{
		PORTA |= (1<<BUZZ);
	}
	else{
		PORTA &= ~(1<<BUZZ);
	}
	
	for(i=size; i>=0 ; i--)
	{
		*(a+i)=ToWriteValue%10;
		ToWriteValue/=10;
	}
	
	alegepoz(&PORTA, &PORTC,0x85, PA0, PA1);
	scrie_caracter(&PORTA,&PORTC,'T',PA0,PA1);
	scrie_caracter(&PORTA,&PORTC,'=',PA0,PA1);
	if(*(a+0)==0)
	{
		
		scrie_caracter(&PORTA,&PORTC,'\0',PA0,PA1);
	}
	else
	{
		scrie_caracter(&PORTA,&PORTC,*(a+0)+'0',PA0,PA1);
	}
	scrie_caracter(&PORTA,&PORTC,*(a+1)+'0',PA0,PA1);
	scrie_caracter(&PORTA,&PORTC,'.',PA0,PA1);
	scrie_caracter(&PORTA,&PORTC,*(a+2)+'0',PA0,PA1);
	scrie_caracter(&PORTA,&PORTC,((char)223),PA0,PA1);
	scrie_caracter(&PORTA,&PORTC,'C',PA0,PA1);
	
	_delay_ms(100);
	
	

}
