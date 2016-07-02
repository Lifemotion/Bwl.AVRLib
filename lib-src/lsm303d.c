#include <avr/io.h>
#include "lsm303d.h"

void  lsm_read_temp(volatile unsigned int * data)
{
	i2c_start();
	i2c_write_byte(0x3C); 
	i2c_write_byte(0x31);
	i2c_start();		  
	i2c_write_byte(0x3D);
	unsigned char h = i2c_read_byte();
	unsigned char l = i2c_read_last_byte();
	*data= h*256+l+8192;
	i2c_stop();
}

void lsm_read_raw(unsigned char * data)
{
	i2c_start();
	i2c_write_byte(0x3C);
	i2c_write_byte(0x03);
	i2c_start();
	i2c_write_byte(0x3D);
	data[0] = i2c_read_byte();
	data[1] = i2c_read_byte();
	data[2] = i2c_read_byte();
	data[3] = i2c_read_byte();
	data[4] = i2c_read_byte();
	data[5] = i2c_read_last_byte();
	i2c_stop();
}

unsigned char _raw [6];
mag_data_t lsm_read()
{
	mag_data_t data;
	lsm_read_raw(_raw);
	data.x=_raw[0]*256+_raw[1]; data.x=data.x+8192;
	data.y=_raw[2]*256+_raw[3]; data.y=data.y+8192;	
	data.z=_raw[4]*256+_raw[5]; data.z=data.z+8192;	
	return data;
}

void lsm_sleep()
{
	i2c_start();
	//02 - Mode
	i2c_write_byte(0x3C);
	i2c_write_byte(0x02);
	i2c_write_byte(LSM_MODE_SLEEP);
	
	//i2c_write_byte(0x00);
	//i2c_write_byte(0b00000111);	
	i2c_stop();	
}

byte lsm_averaging_to_code(byte averaging)
{
	if (averaging==1){return LSM_AVERAGING_1;}
	if (averaging==2){return LSM_AVERAGING_2;}
	if (averaging==4){return LSM_AVERAGING_4;}
	if (averaging==8){return LSM_AVERAGING_8;}
	return LSM_AVERAGING_1;		
}

byte lsm_gain_to_code(byte gain)
{
	if (gain==0){return LSM_GAIN_1;}
	if (gain==1){return LSM_GAIN_1;}
	if (gain==2){return LSM_GAIN_2;}
	if (gain==3){return LSM_GAIN_3;}
	if (gain==4){return LSM_GAIN_4;}
	if (gain==5){return LSM_GAIN_5;}
	if (gain==6){return LSM_GAIN_6;}
	if (gain==7){return LSM_GAIN_7;}
	if (gain==8){return LSM_GAIN_8;}	
	return LSM_GAIN_1;	
}


void lsm_init(byte averaging_code, byte datarate_code, byte gain_code)
{
	PORTC&=(~(1<<PORTC5)); 
	PORTC&=(~(1<<PORTC4)); 
	
	TWSR = 0;
	TWBR = 20;
	
	i2c_start();
	i2c_write_byte(0x3C);
	i2c_write_byte(0x00);
	//00 - CfgA
	//7 - TS
	//6-5 - MA10 Averaging 00 - 0, 01 -2? 10 - 4, 11-8
	//4-2 - Data Output Rate 100 - 15
	//1-0 - Mode 00 - Normal
	i2c_write_byte(LSM_TEMP_ENABLED|averaging_code|datarate_code|LSM_MEASHUREMENT_NORMAL);
	i2c_stop();
	
	i2c_start();
	//01 - CfgB
	//7-5 Gain
	i2c_write_byte(0x3C);
	i2c_write_byte(0x01);
	i2c_write_byte(gain_code);
	i2c_stop();	
	
	i2c_start();
	//02 - Mode
	i2c_write_byte(0x3C);
	i2c_write_byte(0x02);
	i2c_write_byte(LSM_MODE_NORMAL);
	i2c_stop();
}


