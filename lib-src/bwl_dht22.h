/*
 * Bwl lib for DHT22 sensor
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 25.10.2017
 */

#ifndef _DHT22_H_
#define _DHT22_H_

#include <stdint.h>

typedef enum
{
  DHT_ERROR_NONE = 0,
  DHT_BUS_HUNG,
  DHT_ERROR_NOT_PRESENT,
  DHT_ERROR_ACK_TOO_LONG,
  DHT_ERROR_SYNC_TIMEOUT,
  DHT_ERROR_DATA_TIMEOUT,
  DHT_ERROR_CHECKSUM,
  DHT_ERROR_TOOQUICK
} DHT22_ERROR_t;

//вызывать
//прочитать значение температуры и влажности с фиксированной запятой,
//для получения реальных значений нужно разделить на 10
int dht22_read_fixed(char index, int *temperature, int *humidity);
//прочитать значение температуры и влажности с преобразованием во float
int dht22_read_float(char index, float *temperature, float *humidity);
//прочитать значение температуры и влажности с преобразованием в int
int dht22_read_int(char index, int *temperature, int *humidity);

//должно быть реализовано
//установить data-pin DHT22 в указанное состояние: isOutput - вход\выход (DDRx), isHigh - высокий\низкий (PORTx)
void dht22_pin_set(char index, char isOutput, char isHigh);
//считать состояние data-pin DHT22 (PINx)
char dht22_pin_read(char index);
//задержка 2 мкс
void dht22_delay_2us();
//задержка 1,1 мс
void dht22_delay_1100us();

/*
//Example:

#define DHT_SENSOR_PIN A,1 //PORT A, PIN 1
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/delay.h>
#include "bwl_pins.h"
#include "bwl_dht22.h"

void dht22_delay_2us()
{
	_delay_us(2);
}

void dht22_delay_1100us()
{
	_delay_us(1100);
}

void dht22_pin_set(char index, char isOutput, char isHigh)
{
	pin_set_dir(DHT_SENSOR_PIN,isOutput);
	pin_set_out(DHT_SENSOR_PIN,isHigh);
}

char dht22_pin_read(char index)
{
	return pin_get_in(DHT_SENSOR_PIN);
}

void main()
{
	//...
	float temp0;
	float humidity0;
	dht22_read_float (0,&temp0,&humidity0);
	//..
}
*/

#endif /*_DHT22_H_*/
