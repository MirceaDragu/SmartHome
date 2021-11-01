/*
 * LCD.h
 *
 * Created: 7/12/2021 6:52:16 PM
 *  Author: Mircea
 */ 


#ifndef LCD_H_
#define LCD_H_

void scrie_caracter(volatile uint8_t *portrse, volatile uint8_t *portout, char c, int rs, int enable);
void alegepoz(volatile uint8_t *portrse, volatile uint8_t *portout, unsigned int poz, int rs, int enable);
void scrie_text(volatile uint8_t *portrse, volatile uint8_t *portout, char *text, int rs, int enable);
void initLCD(volatile uint8_t *portrse, volatile uint8_t *portout, int rs, int enable);
void clearL1();
void clearL2();





#endif /* LCD_H_ */