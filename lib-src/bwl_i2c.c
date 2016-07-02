/*
 * Bwl I2C Lib
 *
 * Author: Igor Koshelev 
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */ 
#include <avr/io.h>

void i2c_wait()
{
	volatile char i=0;
	while ((!(TWCR & (1 << TWINT)))&(i<250)){i++;}
}

void i2c_start() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	i2c_wait();
}

void i2c_write_byte(char byte) {
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	i2c_wait();
}

char i2c_read_byte() {
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	i2c_wait();
	return TWDR;
}

char i2c_read_last_byte() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	i2c_wait();
	return TWDR;
}

void i2c_stop() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
