/*
 * ADC.h
 *
 * Created: 7/12/2021 7:56:29 PM
 *  Author: Mircea
 */ 


#ifndef ADC_H_
#define ADC_H_

void initADC();
uint16_t readADC(uint8_t pin);
void WriteTemperature(uint8_t size, volatile uint8_t *a);



#endif /* ADC_H_ */