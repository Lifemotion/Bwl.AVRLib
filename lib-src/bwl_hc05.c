/*
 * Bwl ADC lib for HC-05
 *
 * Author: Nickolay Gusev and others
 * Licensed: open-source Apache license
 *
 * Version: 27.10.2017
 */ 

#include "bwl_hc05.h"
#include <string.h>
#include <stdlib.h>
char hc_send_buffer[32]={};

void hc_send_string(char *string)
{
	unsigned	char  i=0;
	while (string[i]>0 && i<512)
	{
		hc_uart_send(string[i]);
		i++;
	}
}

void hc_send_int(int val)
{
	itoa(val,hc_send_buffer,10);
	hc_send_string(hc_send_buffer);
}

void hc_send_long(long val)
{
	ltoa(val,hc_send_buffer,10);
	hc_send_string(hc_send_buffer);
}

void hc_send_line(char *string)
{
	hc_send_string(string);
	hc_uart_send(0xD);
	hc_uart_send(0xA);
}

int hc_init(char* device_name, char* device_password)
{
	char buffer[40];
	int buffer_pointer = 0;
	unsigned long delay = 0;
	hc_key_pin_set(1);
	var_delay_ms(100);
	hc_send_line("AT+RMAAD");
	var_delay_ms(100);
	hc_send_line("AT+ROLE=0");
	var_delay_ms(100);
	hc_send_string("AT+NAME=");
	hc_send_line(device_name);
	var_delay_ms(100);
	hc_send_string("AT+PSWD=");
	hc_send_line(device_password);
	var_delay_ms(100);
	hc_send_string("AT");	
	while(delay++<20000){
		if(hc_uart_received()){
			char ch = hc_uart_get();
			if(ch=='\n')break;
			buffer[buffer_pointer++] = ch;
		}
	}
	hc_send_line("AT+RESET");
	hc_key_pin_set(0);
	if(strstr(device_password, buffer))return 1;
	return 0;
}
