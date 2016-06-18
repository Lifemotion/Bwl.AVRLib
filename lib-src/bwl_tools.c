#include <stdlib.h>
#include <avr/io.h>
#include "bwl_tools.h"

void delay(unsigned int delay)
{
	volatile unsigned long v;
	for (v=0; v<delay;v++)
	{
		v=v;
	}
}
int abs (int i)
{
if (i<0){return -i;}else{return i;}
}


void set_pin_zero(unsigned char pin)
{
	switch(pin)
	{
		case 0x20: cbi(PORTB,0);break;
		case 0x21: cbi(PORTB,1);break;
		case 0x22: cbi(PORTB,2);break;
		case 0x23: cbi(PORTB,3);break;
		case 0x24: cbi(PORTB,4);break;
		case 0x25: cbi(PORTB,5);break;
		case 0x26: cbi(PORTB,6);break;
		case 0x27: cbi(PORTB,7);break;
		
		case 0x30: cbi(PORTC,0);break;
		case 0x31: cbi(PORTC,1);break;
		case 0x32: cbi(PORTC,2);break;
		case 0x33: cbi(PORTC,3);break;
		case 0x34: cbi(PORTC,4);break;
		case 0x35: cbi(PORTC,5);break;
		case 0x36: cbi(PORTC,6);break;
		case 0x37: cbi(PORTC,7);break;
	}
}

void set_pin_one(unsigned char pin)
{
	switch(pin)
	{
		case 0x20: sbi(PORTB,0);break;
		case 0x21: sbi(PORTB,1);break;
		case 0x22: sbi(PORTB,2);break;
		case 0x23: sbi(PORTB,3);break;
		case 0x24: sbi(PORTB,4);break;
		case 0x25: sbi(PORTB,5);break;
		case 0x26: sbi(PORTB,6);break;
		case 0x27: sbi(PORTB,7);break;
		
		case 0x30: sbi(PORTC,0);break;
		case 0x31: sbi(PORTC,1);break;
		case 0x32: sbi(PORTC,2);break;
		case 0x33: sbi(PORTC,3);break;
		case 0x34: sbi(PORTC,4);break;
		case 0x35: sbi(PORTC,5);break;
		case 0x36: sbi(PORTC,6);break;
		case 0x37: sbi(PORTC,7);break;
	}
}

void set_pin_output(unsigned char pin, unsigned char enable)
{
	switch (pin&0b11111000)
	{
		#ifdef PORTA
		case 0x10: setbit(PORTA,pin&0b00000111,enable);break;
		#endif
		#ifdef PORTB
		case 0x20: setbit(PORTB,pin&0b00000111,enable);break;
		#endif
		#ifdef PORTC
		case 0x30: setbit(PORTC,pin&0b00000111,enable);break;
		#endif
		#ifdef PORTD
		case 0x40: setbit(PORTD,pin&0b00000111,enable);break;
		#endif
		#ifdef PORTE
		case 0x50: setbit(PORTE,pin&0b00000111,enable);break;
		#endif
		#ifdef PORTF
		case 0x60: setbit(PORTF,pin&0b00000111,enable);break;
		#endif
	};
}

void set_pin_direction(unsigned char pin, unsigned char is_output)
{
	switch (pin&0b11111000)
	{
		#ifdef DDRA
		case 0x10: setbit(DDRA,pin&0b00000111,is_output);break;
		#endif
		#ifdef DDRB
		case 0x20: setbit(DDRB,pin&0b00000111,is_output);break;
		#endif
		#ifdef DDRC
		case 0x30: setbit(DDRC,pin&0b00000111,is_output);break;
		#endif
		#ifdef DDRD
		case 0x40: setbit(DDRD,pin&0b00000111,is_output);break;
		#endif
		#ifdef DDRE
		case 0x50: setbit(DDRE,pin&0b00000111,is_output);break;
		#endif
		#ifdef DDRF
		case 0x60: setbit(DDRF,pin&0b00000111,is_output);break;
		#endif
	};
}

unsigned char get_pin(unsigned char pin)
{
	switch (pin&0b11111000)
	{
		#ifdef PINA
		case 0x10: return getbit(PINA,pin&0b00000111);break;
		#endif
		#ifdef PINB
		case 0x20: return getbit(PINB,pin&0b00000111);break;
		#endif
		#ifdef PINC
		case 0x30: return getbit(PINC,pin&0b00000111);break;
		#endif
		#ifdef PIND
		case 0x40: return getbit(PIND,pin&0b00000111);break;
		#endif
		#ifdef PINE
		case 0x50: return getbit(PINE,pin&0b00000111);break;
		#endif
		#ifdef PINF
		case 0x60: return getbit(PINF,pin&0b00000111);break;
		#endif
	}
	return 0;
}
