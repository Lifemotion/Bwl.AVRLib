#include <avr/io.h>

void eep_write(unsigned int address, unsigned char data)
{
	while(EECR & (1<<EEPE));
	EEAR = address;
	EEDR = data;
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

unsigned char eep_read(unsigned int address)
{
	while(EECR & (1<<EEPE));
	EEAR = address;
	EECR |= (1<<EERE);
	return EEDR;
}

