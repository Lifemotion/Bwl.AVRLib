/*
 * Bwl lib for strings
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#include "bwl_strings.h"
#include <stdlib.h>

char string_buffer[STRING_BUFFER_SIZE]={};
char string_process_buffer[16]={};
int string_buffer_pos=0;

void string_clear()
{
	for (int i=0; i<STRING_BUFFER_SIZE; i++) string_buffer[i]=0;
	string_buffer_pos=0;
}

void string_add_string(char* string)
{
	unsigned char i=0;
	while (string[i]>0)
	{
		if (string_buffer_pos>STRING_BUFFER_SIZE){return;}
		string_buffer[string_buffer_pos++]=string[i++];
	}
}

void string_add_char(char ch)
{
	if (string_buffer_pos>STRING_BUFFER_SIZE){return;}
	string_buffer[string_buffer_pos++]=ch;
}

void string_add_space()
{
	if (string_buffer_pos>STRING_BUFFER_SIZE){return;}
	string_buffer[string_buffer_pos++]=' ';
}

void string_add_int(int val)
{
	itoa(val,string_process_buffer,10);
	string_add_string(string_process_buffer);
}

void string_add_float(float val,char precision)
{
	dtostrf(val,1,precision,string_process_buffer);
	string_add_string(string_process_buffer);
}

void string_add_crlf()
{
	string_add_string("\r\n");
}


