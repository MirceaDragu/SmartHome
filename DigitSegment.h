/*
 * DigitSegment.h
 *
 * Created: 7/12/2021 6:52:48 PM
 *  Author: Mircea
 */ 


#ifndef DIGITSEGMENT_H_
#define DIGITSEGMENT_H_

void init();
void SHCPpulse();
void STCPpulse();
void BitCalcul(uint8_t k);
void Point();
void Write(uint8_t nr);
void TimeCalcul();
void afisare();
//ISR(TIMER0_OVF_vect);
void init_timer();





#endif /* DIGITSEGMENT_H_ */