/*
 * Bwl UART lib for AVR: mega48/88/168/328
 *
 * Author: Igor Koshelev and others
 * Licenced: open-source Apache license
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "bwl_uart.h"

void uart_init_withdivider(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0A = (0<<U2X0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void uart_disable()
{
	UCSR0B = (0<<RXEN0)|(0<<TXEN0);	
}

void uart_init_withbaud(double clock_khz, double portspeed_baud)
{
		double divider=round(clock_khz*1000.0/(double)portspeed_baud/16.0-1.0);
		uart_init_withdivider(divider);
}

void uart_send( unsigned char byte )
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = byte;
}

 unsigned char uart_received( void )
{
	return (UCSR0A & (1<<RXC0));
}

unsigned char uart_get( void )
{
	if (uart_received())
	{
		return UDR0;
	}
	return 0xFF;
}

void uart_send_string(char *string)
{
	unsigned char i=0;
	while (string[i]>0)
	{
		uart_send(string[i]);
		i+=1;
	}
}

char* buffer="1234567890";
void uart_send_int(char* caption, int parameter)
{
	itoa(parameter,buffer,10);
	uart_send_string(caption);
	uart_send_string(buffer);
	uart_send_string("\n\r");
}


