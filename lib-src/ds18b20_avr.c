/*
 * Bwl lib for DS18b20
 *
 * Author: Andrew Lebedew and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#include "ds18b20_avr.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

typedef unsigned char byte;

// сброс датчика
uint8_t sensor_reset()
{
	int stateSensor=0;
	//Посылаем 0
	set_ow_pin(1,0);
	//Ждем 480 мкс, из даташита
	_delay_us(480);
	// Посылаем 1 (НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	set_ow_pin(0,0);
	//Ждем 60 мкс (из даташита)
	_delay_us(60);
	// Получаем значение с датчика в период 480 мкс (из даташита)
	// возвращаем значение (0=OK, 1=датчик не найден)
	stateSensor=get_ow_pin();
	_delay_us(420);
	return stateSensor;
}


//Чтение бита
uint8_t ds18b20_read_bit(void)
{
	//Сброс встроенного вотчдога
	//ПОЧЕМУ ДОЛГО ВЫПОЛНЯЕТСЯ ФУНКЦИЯ 
    int dataBit=0;
	//Посылаем 0
	set_ow_pin(1,0);
	//Задержка из даташита
    _delay_us(2);
	// Посылаем 1 (НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	set_ow_pin(0,0);
	//Ждем 14 мкс (из даташита)
    _delay_us(4);
    //Получаем состояние
	if (get_ow_pin()) dataBit=1;
    //Ждем 45 мкс (из даташита) и возвращаем значение
    _delay_us(62);
    return dataBit;
}

//Чтение байта
uint8_t ds18b20_read_byte(void)
{
	uint8_t numberBit=8, sensorData=0;
	while(numberBit--){
		// сдвигаем в право на 1 и сохраняем следующее значение
		sensorData>>=1;
		sensorData|=(ds18b20_read_bit()<<7);
	}
	return sensorData;
}

//Отправка бита
void ds18b20_write_bit(uint8_t dataBit)
{
	//Посылаем 0
	set_ow_pin(1,0);
	//Ждем 1 мкс (из даташита)
	_delay_us(2);
	// если хотим отправить 1, посылаем 1 (если нет, оставляем как есть)
	//(НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	if (dataBit==1) set_ow_pin(0,0);
	// ждем 60 мкс (из даташита)
	_delay_us(62);
	set_ow_pin(0,0);
}

// Отправка байта
void ds18b20_write_byte(uint8_t sensorData)
{
	uint8_t numberBit=8;
	while(numberBit--)
	{
		//Отправляем бит и сдвигаем вправо на 1
		ds18b20_write_bit(sensorData&1);
		sensorData>>=1;
	}
}

//Команды управления датчиком
#define SENSOR_CMD_CONVERTTEMP 0x44
#define SENSOR_CMD_RSCRATCHPAD 0xbe
#define SENSOR_CMD_WSCRATCHPAD 0x4e
#define SENSOR_CMD_CPYSCRATCHPAD 0x48
#define SENSOR_CMD_RECEEPROM 0xb8
#define SENSOR_CMD_RPWRSUPPLY 0xb4
#define SENSOR_CMD_SEARCHROM 0xf0
#define SENSOR_CMD_READROM 0x33
#define SENSOR_CMD_MATCHROM 0x55
#define SENSOR_CMD_SKIPROM 0xcc
#define SENSOR_CMD_ALARMSEARCH 0xec
#define SENSOR_CMD_RESOLUTION_9_BIT 0x7f

#define THERM_DECIMAL_STEPS_12BIT 625 //.0625

float ds18b20_get_temperature_float_async()
{
	uint8_t temp_data[2];
	static int result=0;
	sensor_reset();
	ds18b20_write_byte(SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(SENSOR_CMD_RSCRATCHPAD);
	//Младший байт: 7-6-5-4-3-2-1-0. С 7 по 4 целое значение, младшие биты, с 3 по 0 дробные
	temp_data[0]=ds18b20_read_byte();
	//Старший байт: 7-6-5-4-3-2-1-0. С 2 по 0 целое значение, старшие биты, с 8 по 3 - знак
	temp_data[1]=ds18b20_read_byte();
	sensor_reset();
	ds18b20_write_byte(SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(SENSOR_CMD_CONVERTTEMP);
	result = (temp_data[1] << 8) | temp_data[0];
	return result/16.0;
}

float ds18b20_get_temperature_float()
{
	uint8_t temp_data[2];
	static int result=0;
	
	sensor_reset();
	ds18b20_write_byte(SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(SENSOR_CMD_CONVERTTEMP);		
	
	var_delay_ms(750);
	
	sensor_reset();
	ds18b20_write_byte(SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(SENSOR_CMD_RSCRATCHPAD);
	//Младший байт: 7-6-5-4-3-2-1-0. С 7 по 4 целое значение, младшие биты, с 3 по 0 дробные
	temp_data[0]=ds18b20_read_byte();
	//Старший байт: 7-6-5-4-3-2-1-0. С 2 по 0 целое значение, старшие биты, с 8 по 3 - знак
	temp_data[1]=ds18b20_read_byte();
	sensor_reset();
	
	result = (temp_data[1] << 8) | temp_data[0];

	return result/16.0;	
}
