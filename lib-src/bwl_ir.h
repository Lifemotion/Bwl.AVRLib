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
void var_delay_ms(int ms);
void ir_modulation_delay();
void ir_led_set(char state);

/* Example:
void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

void ir_led_set(char state)
{
	setbit(DDRA,7,1);
	setbit(PORTA,7,state);
}

void ir_modulation_delay()
{
	_delay_us(10.5);
}
*/

//вызывать
void ir_send(char data);
void ir_send_string(char* string);
void ir_send_int(int data);
void ir_send_line(char* string);

/* Example:
	ir_send_string("climate_ok=");
	ir_send_int(climate_ok);
	ir_send_line("");}
*/

#endif /* BWL_IR_H_ */

