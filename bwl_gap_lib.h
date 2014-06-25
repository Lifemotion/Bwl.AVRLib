#ifndef GAP_LIB_H_
#define GAP_LIB_H_

#include <avr/io.h>

void gap_delay(unsigned int delay);
void gap_led(char r, char g, char b);
void gap_button_enable();
void gap_button2_enable();
void gap_opt_in1_enable();
void gap_opt_in2_enable();
unsigned char gap_pinb(unsigned char pin);
unsigned char gap_pinc(unsigned char pin);
unsigned char gap_pind(unsigned char pin);
void gap_ddrb(unsigned char pin, unsigned char val);
void gap_ddrc(unsigned char pin, unsigned char val);
void gap_ddrd(unsigned char pin, unsigned char val);
void gap_portb(unsigned char pin, unsigned char val);
void gap_portc(unsigned char pin, unsigned char val);
void gap_portd(unsigned char pin, unsigned char val);
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
