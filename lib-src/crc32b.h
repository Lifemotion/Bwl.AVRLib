#ifndef CRC32B_H_
#define CRC32B_H_

//~71kbytes/sec on 16mhz atmega328p

#define CRC32_POLY 0xEDB88320
#define CRC32_INITIAL 0xFFFFFFFF

uint32_t crc32_value;

__inline__ void crc32b_update(unsigned char databyte)
{
	crc32_value = crc32_value ^ databyte;
	for (unsigned char j = 8; j != 0; j--)
	{
		crc32_value = (crc32_value >> 1) ^ (CRC32_POLY & (-(crc32_value & 1)));
	}
}

__inline__ void crc32b_reset(unsigned char databyte)
{
	crc32_value=CRC32_INITIAL;
}

__inline__ uint32_t crc32_finish(void)
{
	return ~crc32_value;	
}

uint32_t crc32b_compute(unsigned char* data, int length)
{
	crc32_value=CRC32_INITIAL;
	for (unsigned int i=0; i<length; i++)
	{
		crc32b_update(data[i]);
	}
	return crc32_finish();
}

char crc32b_test()
{
	unsigned char test[8] = { 0x31, 0x32, 0x33, 0x34, 0x9b, 0xe3, 0xe0, 0xa3 };
	uint32_t result= crc32b_compute(test,8);
	return (result==0x15b25a56);
}

#endif /* CRC32B_H_ */