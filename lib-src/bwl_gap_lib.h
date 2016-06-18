#ifndef GAP_LIB_H_
#define F_CPU 8000000

#define GAP_LIB_H_
#define bit_set(var, bit)   ((var) |= (uint8_t)(1<<bit))
#define bit_clr(var, bit)   ((var) &= (uint8_t)~(1<<bit))
#define bit_toggle(var, bit)   ((var) ^= (uint8_t)(1<<bit))
#define bit_read(var, bit)   ((var) & (uint8_t)(1<<bit))
#include <avr/io.h>

void gap_delay(double delay);
void gap_led(char r, char g, char b);
void gap_button_enable1();
void gap_button2_enable();
void gap_opt_in1_enable();
void gap_opt_in2_enable();
unsigned int gap_button_portb(unsigned char pin);
unsigned int gap_button1();
unsigned int gap_button2();
unsigned int gap_opt_in1();
unsigned int gap_opt_in2();
void gap_buzzer_play(unsigned int freq, unsigned int time);
void gap_relay1(unsigned char state);
void gap_relay2(unsigned char state);
void gap_uart_485_rx();
void gap_uart_485_tx();
#endif /* GAP_LIB_H_ */
