/*
 * Bwl lib for IR transmission
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#ifndef BWL_IR_H_
#define BWL_IR_H_

//должны быть реализованы
//задержка дл€ получени€ частоты 38 к√ц, ~10-12 мкс
void ir_modulation_delay();
//включить (state>0) или выключить (state=0) » -светодиод
void ir_led_set(char state);

//вызывать
void ir_send(char data);
void ir_send_string(char* string);
void ir_send_int(int data);
void ir_send_long(long data);
void ir_send_line(char* string);

/* Example:
#define F_CPU 8000000
#DEFINE PIN_IR A,1 //PORT A, PIN 1

#include <avr/io.h>
#include <avr/delay.h>
#include "bwl_ir.h"
#include "bwl_pins.h"

void ir_led_set(char state)
{
	pin_set_dir(PIN_IR,1);
	pin_set_out(PIN_IR,state);
}

void ir_modulation_delay()
{
	_delay_us(10.5);
}

void main()
{
	ir_send_string("climate_ok=");
	ir_send_int(climate_ok);
	ir_send_line("");
}
*/

#endif /* BWL_IR_H_ */

