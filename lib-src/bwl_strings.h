/*
 * Bwl lib for strings
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#ifndef BWL_STRINGS
#define BWL_STRINGS

#define STRING_BUFFER_SIZE 512
void string_clear();
void string_add_string(char* string);
void string_add_space();
void string_add_char(char);
void string_add_int(int val);
void string_add_float(float val,char precision);
void string_add_crlf();
char string_buffer[STRING_BUFFER_SIZE];

/* Example
	string_clear();
	string_add_crlf();
	string_add_string("PbWd:ok=");	string_add_int(watchdog_ok);				string_add_string(",");
	string_add_string("w=");		string_add_int(watchdog_warning);			string_add_string(",");
	string_add_string("lo=");		string_add_int(watchdog_loading);			string_add_string(",");
	string_add_string("npw=");		string_add_int(watchdog_no_power);			string_add_string(",");
	string_add_string("sec");		string_add_int(watchdog_sec_to_reset);
	string_add_crlf();
	ir_send_string(string_buffer);
*/

#endif /* BWL_STRINGS */
