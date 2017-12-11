/*
 * Bwl lib for DS18b20
 *
 * Author: Andrew Lebedew and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#include "bwl_ds18b20.h"

#include <stdint.h>

// сброс датчика
uint8_t sensor_reset(char index)
{
	int stateSensor=0;
	//Посылаем 0
	ds18b20_pin_set(index,1,0);
	//Ждем 480 мкс, из даташита
	ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();
	ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();
	// Посылаем 1 (НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	ds18b20_pin_set(index,0,0);
	//Ждем 60 мкс (из даташита)
	ds18b20_delay_60us();
	// Получаем значение с датчика в период 480 мкс (из даташита)
	// возвращаем значение (0=OK, 1=датчик не найден)
	stateSensor=ds18b20_pin_read(index);
	ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();
	ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();ds18b20_delay_60us();
	return stateSensor;
}

//Чтение бита
uint8_t ds18b20_read_bit(char index)
{
	//Сброс встроенного вотчдога
	//ПОЧЕМУ ДОЛГО ВЫПОЛНЯЕТСЯ ФУНКЦИЯ 
    int dataBit=0;
	//Посылаем 0
	ds18b20_pin_set(index,1,0);
	//Задержка из даташита
    ds18b20_delay_2us();
	// Посылаем 1 (НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	ds18b20_pin_set(index,0,0);
	//Ждем 14 мкс (из даташита)
    ds18b20_delay_2us();ds18b20_delay_2us();
    //Получаем состояние
	if (ds18b20_pin_read(index)) dataBit=1;
    //Ждем 45 мкс (из даташита) и возвращаем значение
    ds18b20_delay_60us();
    return dataBit;
}

//Чтение байта
uint8_t ds18b20_read_byte(char index)
{
	uint8_t numberBit=8, sensorData=0;
	while(numberBit--){
		// сдвигаем в право на 1 и сохраняем следующее значение
		sensorData>>=1;
		sensorData|=(ds18b20_read_bit(index)<<7);
	}
	return sensorData;
}

//Отправка бита
void ds18b20_write_bit(char index,uint8_t dataBit)
{
	//Посылаем 0
	ds18b20_pin_set(index,1,0);
	//Ждем 1 мкс (из даташита)
	ds18b20_delay_2us();
	// если хотим отправить 1, посылаем 1 (если нет, оставляем как есть)
	//(НЕ ПОНЯТНО, ПОЧЕМУ НУЖНО УСТАНОВИТЬ ПИН КАК ВХОД)
	if (dataBit==1) ds18b20_pin_set(index,0,0);
	// ждем 60 мкс (из даташита)
	ds18b20_delay_60us();
	ds18b20_pin_set(index,0,0);
}

// Отправка байта
void ds18b20_write_byte(char index,uint8_t sensorData)
{
	uint8_t numberBit=8;
	while(numberBit--)
	{
		//Отправляем бит и сдвигаем вправо на 1
		ds18b20_write_bit(index,sensorData&1);
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

int ds18b20_get_temperature_fixed_async(char index)
{
	uint8_t temp_data[2];
	static int result=0;
	sensor_reset(index);
	ds18b20_write_byte(index,SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(index,SENSOR_CMD_RSCRATCHPAD);
	//Младший байт: 7-6-5-4-3-2-1-0. С 7 по 4 целое значение, младшие биты, с 3 по 0 дробные
	temp_data[0]=ds18b20_read_byte(index);
	//Старший байт: 7-6-5-4-3-2-1-0. С 2 по 0 целое значение, старшие биты, с 8 по 3 - знак
	temp_data[1]=ds18b20_read_byte(index);
	sensor_reset(index);
	ds18b20_write_byte(index,SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(index,SENSOR_CMD_CONVERTTEMP);
	result = (temp_data[1] << 8) | temp_data[0];
	return result;
}

float ds18b20_get_temperature_float_async(char index)
{
	int result=ds18b20_get_temperature_fixed_async(index);
	return result/16.0;
}

int ds18b20_get_temperature_int_async(char index)
{
	int result=ds18b20_get_temperature_fixed_async(index);
	return result/16;
}

int ds18b20_get_temperature_fixed(char index)
{
	uint8_t temp_data[2];
	static int result=0;
	
	sensor_reset(index);
	ds18b20_write_byte(index,SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(index,SENSOR_CMD_CONVERTTEMP);
	
	ds18b20_delay_750ms(index);
	
	sensor_reset(index);
	ds18b20_write_byte(index,SENSOR_CMD_SKIPROM);
	ds18b20_write_byte(index,SENSOR_CMD_RSCRATCHPAD);
	//Младший байт: 7-6-5-4-3-2-1-0. С 7 по 4 целое значение, младшие биты, с 3 по 0 дробные
	temp_data[0]=ds18b20_read_byte(index);
	//Старший байт: 7-6-5-4-3-2-1-0. С 2 по 0 целое значение, старшие биты, с 8 по 3 - знак
	temp_data[1]=ds18b20_read_byte(index);
	sensor_reset(index);
	
	result = (temp_data[1] << 8) | temp_data[0];

	return result;
}

float ds18b20_get_temperature_float(char index)
{
	int result=ds18b20_get_temperature_fixed(index);
	return result/16.0;
}

int ds18b20_get_temperature_int(char index)
{
	int result=ds18b20_get_temperature_fixed(index);
	return result/16;
}