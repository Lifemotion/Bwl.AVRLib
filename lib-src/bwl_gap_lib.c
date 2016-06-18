#include <avr/io.h>
#include <avr/wdt.h>
#include "bwl_gap_lib.h"
#include <util/delay.h>

void gap_delay(double delay)
{

		//_delay_ms(delay);
}

void gap_led(char r, char g, char b)
{
	DDRB|=0b00000111;
	unsigned char pb=PORTB;
	pb=pb&0b11111000;
	if (r){pb|=4;}
	if (g){pb|=1;}
	if (b){pb|=2;}
	PORTB=pb;
	return;
}

void gap_button_enable1()
{
	DDRB&=0b11110111;
	PORTB|=0b00001000;
	return;
}

void gap_button2_enable()
{
	DDRB&=0b11101111;
	PORTB|=0b00010000;
	return;
}

void gap_opt_in1_enable()
{
	DDRC&= 0b11111110;
	PORTC|=0b00000001;
	return;
}

void gap_opt_in2_enable()
{
	DDRC&= 0b11111101;
	PORTC|=0b00000010;
	return;
}

unsigned int gap_button_portb(unsigned char pin)
{
	if (!bit_read(PINB,pin))
	{
		volatile int wait=0;
		do
		{
			wait++;
			gap_delay(100);
		} while (!bit_read(PINB,pin));
		return wait;
	}
	return 0;
}

unsigned int gap_button1()
{
	gap_button_enable1();
	return gap_button_portb(3);
};

unsigned int gap_button2()
{
	gap_button2_enable();	
	return gap_button_portb(4);
};

unsigned int gap_opt_in1()
{
	gap_opt_in1_enable();
	return (bit_read(PINC,0)==0);
};

unsigned int gap_opt_in2()
{
	gap_opt_in2_enable();
	return (bit_read(PINC,1)==0);
};

void gap_buzzer_play(unsigned int freq, unsigned int time)
{
	bit_set(DDRC,5);
	double pause=1000.0/freq;
	unsigned int cc=freq/10;
	for (unsigned int i=0; i<time; i++)
	{
		for (unsigned int m=0; m<cc; m++)
		{
			bit_set(PORTC,5);
			gap_delay(pause);
			bit_clr(PORTC,5);
		}
	}
	bit_clr(DDRC,5);
}

void gap_relay1(unsigned char state)
{
	bit_set(DDRD,7);
	if (state){bit_set(PORTD,7);}else{bit_clr(PORTD,7);}
}

void gap_relay2(unsigned char state)
{
	bit_set(DDRD,6);
	if (state){bit_set(PORTD,6);}else{bit_clr(PORTD,6);}
}

void gap_uart_485_tx()
{bit_set(DDRB,5); bit_set(PORTB,5);	};

void gap_uart_485_rx()
{bit_set(DDRB,5);bit_clr(PORTB,5);	};

void sserial_send_start()
{bit_set(DDRB,5); bit_set(PORTB,5);	};

void sserial_send_end()
{bit_set(DDRB,5);bit_clr(PORTB,5);	};

void gap_power_out(unsigned char out, unsigned char state)
{
	if (out==1)
	{
		if (state>0){bit_set(DDRD,2);bit_set(PORTD,2);} else {bit_set(DDRD,2);bit_clr(PORTD,2);}
	}
	if (out==2)
	{
		if (state>0){bit_set(DDRD,3);bit_set(PORTD,4);} else {bit_set(DDRD,3);bit_clr(PORTD,3);}
	}
	if (out==3)
	{
			if (state>0){bit_set(DDRD,4);bit_set(PORTD,4);} else {bit_set(DDRD,4);bit_clr(PORTD,4);}
	}
	if (out==4)
	{
		if (state>0){bit_set(DDRD,5);bit_set(PORTD,5);} else {bit_set(DDRD,5);bit_clr(PORTD,5);}
	}
}