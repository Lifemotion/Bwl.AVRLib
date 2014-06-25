/*
 * Bwl UART lib for AVR: mega48/88/168/328
 *
 * Author: Igor Koshelev and others
 * Licenced: open-source Apache license
 */ 

#ifndef BWL_UART_H_
#define BWL_UART_H_

void uart_init_withdivider(unsigned int ubrr);
void uart_init_withbaud(double clock_khz, double portspeed_baud);
void uart_send( unsigned char byte );
unsigned char uart_peek( void );

#endif /* BWL_UART_H_ */
