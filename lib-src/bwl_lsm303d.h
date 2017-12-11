#ifndef HMC5983_H_
#define HMC5983_H_

typedef struct
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
} mag_data_t;

typedef struct
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
} acc_data_t;

typedef unsigned char byte;

#define LSM_AVERAGING_1 0b00000000
#define LSM_AVERAGING_2 0b00100000
#define LSM_AVERAGING_4 0b01000000
#define LSM_AVERAGING_8 0b01100000

#define LSM_DATARATE_0_75	0b00000000
#define LSM_DATARATE_15		0b00010000
#define LSM_DATARATE_30		0b00010100
#define LSM_DATARATE_75		0b00011000
#define LSM_DATARATE_220	0b00011100

#define LSM_GAIN_8		0b00000000
#define LSM_GAIN_7		0b00100000
#define LSM_GAIN_6		0b01000000
#define LSM_GAIN_5		0b01100000
#define LSM_GAIN_4		0b10000000
#define LSM_GAIN_3		0b10100000
#define LSM_GAIN_2		0b11000000
#define LSM_GAIN_1		0b11100000

#define  LSM_MEASHUREMENT_NORMAL	0b00000000
#define  LSM_MODE_NORMAL	0b00000000
#define  LSM_MODE_SLEEP		0b00000011
#define  LSM_TEMP_ENABLED	0b10000000

//необходимо реализовать (см bwl_i2c.h)
void i2c_wait();
void i2c_start() ;
void i2c_write_byte(char byte);
char i2c_read_byte();
char i2c_read_last_byte();
void i2c_stop();

//можно использовать
void lsm_init(byte averaging_code, byte datarate_code, byte gain_code);
void lsm_sleep();
char lsm_who_i_am();

unsigned int lsm_read_temp();
mag_data_t lsm_read_mag();
acc_data_t lsm_read_acc();

#endif /* HMC5983_H_ */