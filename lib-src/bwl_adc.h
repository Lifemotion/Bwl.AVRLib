/*
 * bwl_adc.h
 *
 * Created: 28.03.2014 14:45:58
 *  Author: Igor
 */ 


#ifndef BWL_ADC_H_
#define BWL_ADC_H_


void adcInit (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler);
void adcOff (void);
unsigned int adcReadOnce (void);


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



#endif /* BWL_ADC_H_ */