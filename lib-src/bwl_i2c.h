/*
 * Bwl I2C Lib
 *
 * Author: Igor Koshelev 
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */ 

#ifndef BWL_I2C_H_
#define BWL_I2C_H_

void i2c_wait();
void i2c_start() ;
void i2c_write_byte(char byte) ;
char i2c_read_byte() ;
char i2c_read_last_byte() ;
void i2c_stop();

/*
//Example:

#define PIN_SCL C,4
#define PIN_SDA C,5

#include <avr/io.h>
#include "bwl_pins.h"
#include "bwl_i2c.h"

void main()
{
	//Enable pull-ups for SCL & SDA pins
	pin_input_pullup(PIN_SCL);
	pin_input_pullup(PIN_SDA);
	//TWSR – TWI Status Register
	TWSR = 0;	
	//TWBR – TWI Bit Rate Register
	TWBR = 20;
	
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x85);
	i2c_start();
	i2c_write_byte(0x3B);
	unsigned char l = i2c_read_byte();
	unsigned char h = i2c_read_last_byte();
	i2c_stop();
}
*/

#endif /* BWL_I2C_H_ */