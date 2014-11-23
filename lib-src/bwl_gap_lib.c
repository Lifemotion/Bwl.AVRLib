/*
 * gap_lib.c
 *
 * Created: 03.11.2013 23:56:21
 *  Author: Igor
 */ 
#include <avr/io.h>



void gap_delay(unsigned int delay)
{
	volatile unsigned long v;
	for (v=0; v<delay;v++)
	{
		v=v;
	}
}

void gap_led(char r, char g, char b)
{
	DDRB|=0b00000111;
	unsigned char pb=PORTB;
	pb=pb&0b11111000;
	if (!r){pb|=4;}
	if (!g){pb|=1;}
	if (!b){pb|=2;}
	PORTB=pb;
	return;
}

void gap_button_enable()
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

unsigned char gap_pinb(unsigned char pin)
{
	return ((PINB&(1<<pin))==0);
}
unsigned char gap_pinc(unsigned char pin)
{
	return ((PINC&(1<<pin))==0);
}
unsigned char gap_pind(unsigned char pin)
{
	return ((PIND&(1<<pin))==0);
}

void gap_ddrc(unsigned char pin, unsigned char val)
{
	if (val){DDRC|=1<<pin;}else{DDRC&=(~(1<<pin));}
}

void gap_portc(unsigned char pin, unsigned char val)
{
	if (val){PORTC|=1<<pin;	}else{PORTC&=(~(1<<pin));}
}
void gap_ddrd(unsigned char pin, unsigned char val)
{
	if (val){DDRD|=1<<pin;}else{DDRD&=(~(1<<pin));}
}

void gap_portd(unsigned char pin, unsigned char val)
{
	if (val){PORTD|=1<<pin;	}else{PORTD&=(~(1<<pin));}
}
void gap_ddrb(unsigned char pin, unsigned char val)
{
	if (val){DDRB|=1<<pin;}else{DDRB&=(~(1<<pin));}
}

void gap_portb(unsigned char pin, unsigned char val)
{
	if (val){PORTB|=1<<pin;	}else{PORTB&=(~(1<<pin));}
}
unsigned int gap_button_portb(unsigned char pin)
{
	if (gap_pinb(pin))
	{
		volatile int wait=0;
		do
		{
			wait++;
			gap_delay(1000);
		} while (gap_pinb(pin));
		return wait;
	}
	return 0;
}

unsigned int gap_button1()
{
	gap_button_enable();
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
	return gap_pinc(0);
};

void gap_buzzer_play(unsigned int freq, unsigned int time)
{
	gap_ddrc(5,1);
	unsigned int pause=30000/freq;
	unsigned int cc=freq/10;
	for (unsigned int i=0; i<time; i++)
	{
		for (unsigned int m=0; m<cc; m++)
		{
			gap_portc(5,1);
			gap_delay(pause);
			gap_portc(5,0);
		}
	}
	gap_ddrc(5,0);
}

void gap_relay1(unsigned char state)
{
	gap_ddrd(7,state);
	gap_portd(7,state);
}
void gap_relay2(unsigned char state)
{
	gap_ddrd(6,state);
	gap_portd(6,state);
}


void gap_uart_485_rx()
{
	gap_portb(5,0);
	gap_ddrb(5,1);
}

void gap_uart_485_tx()
{
	gap_portb(5,1);
	gap_ddrb(5,1);
}

void catuart_tx_off()
{
	gap_uart_485_rx();
}

void catuart_tx_on()
{
	gap_uart_485_tx();
}

void gap_power_out(unsigned char out, unsigned char state)
{
	if (out==1)
	{
		if (state>0){gap_ddrd(2,1);gap_portd(2,1);} else {gap_ddrd(2,1);gap_portd(2,0);}
	}
	if (out==2)
	{
		if (state>0){gap_ddrd(3,1);gap_portd(3,1);} else {gap_ddrd(3,1);gap_portd(3,0);}
	}
	if (out==3)
	{
		if (state>0){gap_ddrd(4,1);gap_portd(4,1);} else {gap_ddrd(4,1);gap_portd(4,0);}
	}
	if (out==4)
	{
		if (state>0){gap_ddrd(5,1);gap_portd(5,1);} else {gap_ddrd(5,1);gap_portd(5,0);}
	}
}