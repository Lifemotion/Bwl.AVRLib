#include <stdlib.h>

void delay(unsigned int delay)
{
	volatile unsigned long v;
	for (v=0; v<delay;v++)
	{
		v=v;
	}
}
int abs (int i)
{
if (i<0){return -i;}else{return i;}
}

