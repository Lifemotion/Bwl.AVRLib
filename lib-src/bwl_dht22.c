#include "bwl_dht22.h"

#define DHT22_DATA_BIT_COUNT 41

int dht22_read_fixed(char index, int *temperature, int *humidity)
{
	uint8_t retryCount;
	uint8_t bitTimes[DHT22_DATA_BIT_COUNT];
	int currentHumidity;
	int currentTemperature;
	uint8_t checkSum, csPart1, csPart2, csPart3, csPart4;
	int i;
	currentHumidity = 0;
	currentTemperature = 0;
	checkSum = 0;	
	for(i = 0; i < DHT22_DATA_BIT_COUNT; i++)
	{
		bitTimes[i] = 0;
	}
	dht22_pin_set(index,0,0);
	retryCount = 0;
	do
	{
		if (retryCount > 125)
		{
			return DHT_BUS_HUNG;
		}
		retryCount++;
		dht22_delay_2us();
	} while(!dht22_pin_read(index));
	dht22_pin_set(index,1,0);
	dht22_delay_1100us();
	dht22_pin_set(index,0,0);
	retryCount = 0;
	do
	{
		if (retryCount > 25) //(Spec is 20 to 40 us, 25*2 == 50 us)
		{
			return DHT_ERROR_NOT_PRESENT;
		}
		retryCount++;
		dht22_delay_2us();
	} while(!dht22_pin_read(index));
	retryCount = 0;
	do
	{
		if (retryCount > 50) //(Spec is 80 us, 50*2 == 100 us)
		{
			return DHT_ERROR_ACK_TOO_LONG;
		}
		retryCount++;
		dht22_delay_2us();
	} while(dht22_pin_read(index));
	// Read the 40 bit data stream
	for(i = 0; i < DHT22_DATA_BIT_COUNT; i++)
	{
		// Find the start of the sync pulse
		retryCount = 0;
		do
		{
			if (retryCount > 35) //(Spec is 50 us, 35*2 == 70 us)
			{
				return DHT_ERROR_SYNC_TIMEOUT;
			}
			retryCount++;
			dht22_delay_2us();
		} while(!dht22_pin_read(index));
		// Measure the width of the data pulse
		retryCount = 0;
		do
		{
			if (retryCount > 50) //(Spec is 80 us, 50*2 == 100 us)
			{
				return DHT_ERROR_DATA_TIMEOUT;
			}
			retryCount++;
			dht22_delay_2us();
		} while(dht22_pin_read(index));
		bitTimes[i] = retryCount;
	}
	// Now bitTimes have the number of retries (us *2)
	// that were needed to find the end of each data bit
	// Spec: 0 is 26 to 28 us
	// Spec: 1 is 70 us
	// bitTimes[x] <= 11 is a 0
	// bitTimes[x] >  11 is a 1
	// Note: the bits are offset by one from the data sheet, not sure why
	for(i = 0; i < 16; i++)
	{
	    if(bitTimes[i + 1] > 11)
		{
			currentHumidity |= (1 << (15 - i));
		}
	}
	for(i = 0; i < 16; i++)
	{
		if(bitTimes[i + 17] > 11)
		{
			currentTemperature |= (1 << (15 - i));
		}
	}
	for(i = 0; i < 8; i++)
	{
		if(bitTimes[i + 33] > 11)
		{
			checkSum |= (1 << (7 - i));
		}
	}

	*humidity = (currentHumidity & 0x7FFF);
	
	if(currentTemperature & 0x8000)
	{
		// Below zero, non standard way of encoding negative numbers!
		currentTemperature &= 0x7FFF;
		*temperature = -currentTemperature;
	}
	else
	{
		*temperature = currentTemperature;
	}

	csPart1 = currentHumidity >> 8;
	csPart2 = currentHumidity & 0xFF;
	csPart3 = currentTemperature >> 8;
	csPart4 = currentTemperature & 0xFF;
	
	if(checkSum == ((csPart1 + csPart2 + csPart3 + csPart4) & 0xFF))
	{
		return DHT_ERROR_NONE;
	}
	return DHT_ERROR_CHECKSUM;
}

int dht22_read_float(char index, float *temperature, float *humidity)
{
	int int_temp=0;
	int int_humi=0;
	int result=dht22_read_fixed(index,&int_temp,&int_humi);
	*temperature = ((float) int_temp)/10.0;
	*humidity = ((float) int_humi)/10.0;
	return result;
}

int dht22_read_int(char index, int *temperature, int *humidity)
{
	int int_temp=0;
	int int_humi=0;
	int result=dht22_read_fixed(index,&int_temp,&int_humi);
	*temperature = int_temp/10;
	*humidity = int_humi/10;
	return result;
}