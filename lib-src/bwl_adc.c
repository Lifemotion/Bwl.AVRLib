/*
 * bwl_adc.c
 *
 * Created: 28.03.2014 14:46:10
 *  Author: Igor
 */ 

#include <avr/io.h>

#define ADC_MUX_ADC0 0
#define ADC_MUX_ADC1 1
#define ADC_MUX_ADC2 2
#define ADC_MUX_ADC3 3
#define ADC_MUX_ADC4 4
#define ADC_MUX_ADC5 5
#define ADC_MUX_ADC6 6
#define ADC_MUX_ADC7 7
#define ADC_MUX_ADC8 8
#define ADC_MUX_1_1V 14
#define ADC_MUX_0V 15

#define ADC_ADJUST_LEFT 1
#define ADC_ADJUST_RIGHT 0

#define ADC_REFS_EXTERNAL 0
#define ADC_REFS_AVCC 1
#define ADC_REFS_INTERNAL 3

#define ADC_PRESCALER_2 0
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7

void adc_init (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler){
	
	ADCSRA = (1 << ADEN)|(prescaler << ADPS0);
	ADMUX  = (refs << REFS0)|(adjust << ADLAR)|(mux << MUX0);
}

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
