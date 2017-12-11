#include <avr/io.h>
#include "bwl_lsm303d.h"

unsigned int lsm_read_temp()
{
	i2c_start();
	i2c_write_byte(0x3A); 
	i2c_write_byte(0x85);
	i2c_start();		  
	i2c_write_byte(0x3B);
	unsigned char l = i2c_read_byte();
	unsigned char h = i2c_read_last_byte();
	i2c_stop();
	return h*256+l;
}

void lsm_read_raw(unsigned char * data)
{
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x88);
	i2c_start();
	i2c_write_byte(0x3B);
	data[0] = i2c_read_byte();
	data[1] = i2c_read_byte();
	data[2] = i2c_read_byte();
	data[3] = i2c_read_byte();
	data[4] = i2c_read_byte();
	data[5] = i2c_read_last_byte();
	i2c_stop();
}

unsigned char _raw [6];
mag_data_t lsm_read_mag()
{
	mag_data_t data;
	lsm_read_raw(_raw);
	data.x=_raw[0]*256+_raw[1]; data.x=data.x+8192;
	data.y=_raw[2]*256+_raw[3]; data.y=data.y+8192;	
	data.z=_raw[4]*256+_raw[5]; data.z=data.z+8192;	
	return data;
}

void lsm_read_raw_acc(unsigned char * data)
{
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0xA8);
	i2c_start();
	i2c_write_byte(0x3B);
	data[0] = i2c_read_byte();
	data[1] = i2c_read_byte();
	data[2] = i2c_read_byte();
	data[3] = i2c_read_byte();
	data[4] = i2c_read_byte();
	data[5] = i2c_read_last_byte();
	i2c_stop();
}

unsigned char data = 0;
char lsm_who_i_am()
{
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x0f);
	i2c_start();
	i2c_write_byte(0x3B);
	data = i2c_read_last_byte();
	i2c_stop();
	if(data == 0x49)return 1;
	return 0;
}

acc_data_t lsm_read_acc()
{
	acc_data_t data;
	lsm_read_raw_acc(_raw);
	data.x=_raw[0]*256+_raw[1]; data.x=data.x+8192;
	data.y=_raw[2]*256+_raw[3]; data.y=data.y+8192;
	data.z=_raw[4]*256+_raw[5]; data.z=data.z+8192;
	return data;
}

void lsm_sleep()
{
	i2c_start();
	//02 - Mode
	i2c_write_byte(0x3A);
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
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x1f);
	i2c_write_byte(0x00);
	i2c_stop();
	
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x20);
	i2c_write_byte(0x4F);
	i2c_stop();
	
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x21);
	i2c_write_byte(0xC0);
	i2c_stop();
	
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x23);
	i2c_write_byte(0x00);
	i2c_stop();

	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x24);
	i2c_write_byte(0xF0);
	i2c_stop();
	
	i2c_start();
	i2c_write_byte(0x3A);
	i2c_write_byte(0x26);
	i2c_write_byte(0x80);
	i2c_stop();
}


