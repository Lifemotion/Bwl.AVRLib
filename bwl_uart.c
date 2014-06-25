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

void uart_init_withdivider(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0A = (0<<U2X0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void uart_init_withbaud(double clock_khz, double portspeed_baud)
{
	if (clock_khz==8000.0)
	{
		if (portspeed_baud==1200){uart_init_withdivider(416);}
		if (portspeed_baud==2400){uart_init_withdivider(207);}
		if (portspeed_baud==4800){uart_init_withdivider(103);}
		if (portspeed_baud==9600){uart_init_withdivider(51);}
		if (portspeed_baud==19200){uart_init_withdivider(25);}
		if (portspeed_baud==38400){uart_init_withdivider(12);}
		if (portspeed_baud==115200){uart_init_withdivider(3);}
	}else
	{
		double divider=round(clock_khz*1000.0/(double)portspeed_baud/16.0-1.0);
		uart_init_withdivider(divider);
	}
}

void uart_send( unsigned char byte )
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = byte;
}

unsigned char uart_peek( void )
{
	if ( (UCSR0A & (1<<RXC0)) )
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


