#include <avr/io.h>

void clock_setdivider(int divider){

	if (divider==1){	CLKPR=(1<<CLKPCE);CLKPR=0;}
	if (divider==2){	CLKPR=(1<<CLKPCE);CLKPR=1;}
	if (divider==4){	CLKPR=(1<<CLKPCE);CLKPR=2;}
	if (divider==8){	CLKPR=(1<<CLKPCE);CLKPR=3;}
	if (divider==16){	CLKPR=(1<<CLKPCE);CLKPR=4;}
	if (divider==32){	CLKPR=(1<<CLKPCE);CLKPR=5;}
	if (divider==64){	CLKPR=(1<<CLKPCE);CLKPR=6;}
	if (divider==128){	CLKPR=(1<<CLKPCE);CLKPR=7;}
	if (divider==256){	CLKPR=(1<<CLKPCE);CLKPR=8;}
}