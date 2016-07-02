/*
 * Bwl ADC lib for AVR: mega48/88/168/328/324/164/2560/1280
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */ 

#include <avr/io.h>
#include "bwl_adc.h"


void adc_off (void){
	ADCSRA = (0 << ADEN)|(0 << ADPS1)|(0 << ADPS0);
	ADMUX  = (0 << REFS1)|(0 << REFS0)|(0 << ADLAR)|(0 << MUX0)|(0 << MUX1)|(0 << MUX2)|(0 << MUX3);
}

unsigned int adc_read_once (void){
	unsigned int data;
	
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0);
	data = ADCL+(ADCH<<8);

	return data;
}

void adc_init_mux5 (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler){
	
	ADCSRA = (1 << ADEN)|(prescaler << ADPS0);
	ADCSRB = (1<<MUX5);
	ADMUX  = (refs << REFS0)|(adjust << ADLAR)|(mux << MUX0);
	adc_read_once();
}

void adc_init (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler){
	
	ADCSRA = (1 << ADEN)|(prescaler << ADPS0);
	ADCSRB = 0;
	ADMUX  = (refs << REFS0)|(adjust << ADLAR)|(mux << MUX0);
	adc_read_once();
}

int adc_read_average(int count )
{
	unsigned long sum=0;
	for (int i=0; i<count; i++)
	{
		sum+=adc_read_once();
	}
	return sum/count;
}
