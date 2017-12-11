/*
 * Bwl lib for DS18b20
 *
 * Author: Andrew Lebedew and others
 * Licensed: open-source Apache license
 *
 * Version: 25.10.2017
 */

#ifndef DS18B20_AVR_H_
#define DS18B20_AVR_H_

//предоставляет функции
//измерить температуру и выдать результат в целочисленной форме
//для получения значения температуры результат разделить на 16
int ds18b20_get_temperature_fixed(char index);
//измерить температуру и выдать результат в форме float. более точно
float ds18b20_get_temperature_float(char index);
//измерить температуру и выдать результат в форме int. более точно
int ds18b20_get_temperature_int(char index);

//измерить температуру без задержки и выдать результат в целочисленной форме
//для получения значения температуры результат разделить на 16
int ds18b20_get_temperature_fixed_async(char index);
//измерить температуру без задержки и выдать результат в форме float. более точно
float ds18b20_get_temperature_float_async(char index);
//измерить температуру без задержки и выдать результат в форме int. более точно
int ds18b20_get_temperature_int_async(char index);

//требует реализации функций
//установить пин, к которому подключен датчик, в режим isOutput (1-выход, 0-вход), и в состояние isHigh.
void ds18b20_pin_set(char index, char isOutput, char isHigh);
//считать значение пина, к которому подключен датчик
char ds18b20_pin_read(char index);
//задержка 2 мкс
void ds18b20_delay_2us();
//задержка 60 мкс
void ds18b20_delay_60us();
//задержка 750 ms
void ds18b20_delay_750ms();

/*
//Example:

#define TEMP_SENSOR_PIN A,1 //PORT A, PIN 1
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/delay.h>
#include "bwl_pins.h"
#include "bwl_ds18b20.h"

void ds18b20_delay_2us()
{
	_delay_us(2);
}

void ds18b20_delay_60us()
{
	_delay_us(60);
}

void ds18b20_delay_750ms()
{
	_delay_ms(750);
}

void ds18b20_pin_set(char index, char isOutput, char isHigh)
{
	pin_set_dir(TEMP_SENSOR_PIN,isOutput);
	pin_set_out(TEMP_SENSOR_PIN,isHigh);
}

char ds18b20_pin_read(char index)
{
	return pin_get_in(TEMP_SENSOR_PIN);
}

void main()
{
	//...
	float temp0=ds18b20_get_temperature_float(0);
	//..
}
*/

#endif