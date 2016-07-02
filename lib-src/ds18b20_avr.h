/*
 * Bwl lib for DS18b20
 *
 * Author: Andrew Lebedew and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#ifndef DS18B20_AVR_H_
#define DS18B20_AVR_H_
typedef unsigned char byte;

#include "../Cf.Orlan.Hardware.PowerBoard.Fw/board/board.h"

//предоставляет функции
//измерить температуру и выдать результат в целочисленной форме
int ds18b20_get_temperature_int();
//измерить температуру и выдать результат в форме float. более точно
float ds18b20_get_temperature_float();
float ds18b20_get_temperature_float_async();

//требует реализации функций
//установить пин, к которому подключен датчик, в режим mode (1-выход, 0-вход), и в состояние state.
void set_ow_pin(byte mode, byte state);
//считать значение пина, к которому подключен датчик
unsigned char get_ow_pin();

/*
#define TEMP_SENSOR_PIN 1
void set_ow_pin(byte mode, byte state)
{
if (state){PORTC|=1<<TEMP_SENSOR_PIN;	}else{PORTC&=(~(1<<TEMP_SENSOR_PIN));}
if (mode){DDRC|=1<<TEMP_SENSOR_PIN;	}else{DDRC&=(~(1<<TEMP_SENSOR_PIN));}
}

unsigned char get_ow_pin()
{
return ((PINC&(1<<TEMP_SENSOR_PIN)));
}
*/

#endif