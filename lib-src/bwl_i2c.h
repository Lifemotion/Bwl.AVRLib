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

/*Need to enable pull-ups on I2C pins and set I2C bitrate
	PORTC&=(~(1<<PORTC5));
	PORTC&=(~(1<<PORTC4));
	
	//TWSR – TWI Status Register
	TWSR = 0;
	
	//TWBR – TWI Bit Rate Register
	TWBR = 20;
*/

#endif /* BWL_I2C_H_ */