#ifndef TIMER1_H_
#define TIMER1_H_

void timer1_set(double interval, double freqMHz )
{
	unsigned int divider=(unsigned int)(512.0*interval*freqMHz);
	TCCR1A=(0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
	TCCR1B=(0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(1<<CS10);
	OCR1AH=divider>>7;
	OCR1AL=divider&127;
}

unsigned char timer1_triggered()
{
	if (TIFR1&(1<<OCF1A))
	{
		TIFR1|=(1<<OCF1A);
		return 1;
	}
	return 0;
}

#endif /* TIMER1_H_ */