/*
 * Bwl ADC lib for AVR: mega48/88/168/328/324/164/2560/1280
 *
 * Author: Igor Koshelev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#ifndef BWL_ADC_H_
#define BWL_ADC_H_

//enable & setup ADC, mux - ADC channel 0..7, adjust - right\left result adjustment (default - right), prescaler - ADC clock divider, ADC clock should be 50..200 kHz
void adc_init (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler);
//enable & setup ADC for channells 8..15, mux - ADC channel+8, adjust - right\left result adjustment (default - right), prescaler - ADC clock divider, ADC clock should be 50..200 kHz
void adc_init_mux5 (unsigned char mux, unsigned char adjust, unsigned char refs, unsigned char prescaler);
//disable ADC
void adc_off (void);
//ADC single read
unsigned int adc_read_once (void);
//ADC read and averaging, count - number of reads
int adc_read_average(int count);

/* Example:
	adc_init(ADC_MUX_ADC2,ADC_ADJUST_RIGHT,ADC_REFS_INTERNAL_1_1,ADC_PRESCALER_64);
	int result=adc_read_average(4);
*/

#define ADC_MUX_ADC0 0
#define ADC_MUX_ADC1 1
#define ADC_MUX_ADC2 2
#define ADC_MUX_ADC3 3
#define ADC_MUX_ADC4 4
#define ADC_MUX_ADC5 5
#define ADC_MUX_ADC6 6
#define ADC_MUX_ADC7 7

#define ADC_MUX_ADCDIFF_1_0_X10 9
#define ADC_MUX_ADCDIFF_1_0_X200 11
#define ADC_MUX_ADCDIFF_3_2_X10 13
#define ADC_MUX_ADCDIFF_3_2_X200 15

#define ADC_MUX_ADCDIFF_9_8_X10 9
#define ADC_MUX_ADCDIFF_9_8_X200 11
#define ADC_MUX_ADCDIFF_11_10_X10 13
#define ADC_MUX_ADCDIFF_11_10_X200 15

/*
#define ADC_MUX_ADC_TEMP 8
#define ADC_MUX_1_1V 14
#define ADC_MUX_0V 15
*/

#define ADC_ADJUST_LEFT 1
#define ADC_ADJUST_RIGHT 0

#define ADC_REFS_EXTERNAL 0
#define ADC_REFS_AVCC 1
#define ADC_REFS_INTERNAL_2_56 3
#define ADC_REFS_INTERNAL_1_1 2

#define ADC_PRESCALER_2 0
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7

#define ADC_DEFAULTS ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_2_56, ADC_PRESCALER_16

#endif /* BWL_ADC_H_ */