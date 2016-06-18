#ifndef CRC16_H_
#define CRC16_H_

#define CRC16_POLY 0xA001
#define CRC16_INITIAL 0xFFFF
//#include <util/crc16.h>
uint16_t crc16_value;

void crc16_update(unsigned char databyte)
{
	{
		int i;
		crc16_value ^= databyte;
		for (i = 0; i < 8; ++i)
		{
			if (crc16_value & 1)
			crc16_value = (crc16_value >> 1) ^ 0xA001;
			else
			crc16_value = (crc16_value >> 1);
		}
	}
}

void crc16_reset()
{
	crc16_value=CRC16_INITIAL;
}

uint32_t crc16_finish(void)
{
	return ~crc16_value;	
}

uint32_t crc16_compute(unsigned char* data, int length)
{
	crc16_reset();
	for (unsigned int i=0; i<length; i++)
	{
		crc16_update(data[i]);
	}
	return crc16_finish();
}
/*
uint32_t crc16_compute(unsigned char* data, int length)
{
	crc16_reset();
	for (unsigned int i=0; i<length; i++)
	{
		crc16_value=_crc16_update(crc16_value,data[i]);
	}
	return crc16_finish();
}
*/
char crc16_test()
{
	unsigned char test[4] = { 0x31, 0x32, 0x33, 0x34 };
	uint16_t result= crc16_compute(test,4);
	return (result==0x15b2);
}

#endif /* CRC32B_H_ */