/*
 * Bwl lib for easy AVR pin manipulation
 *
 * Author: Igor Koshelev 
 * Licensed: open-source Apache license
 *
 * Version: 11.11.2016
 */
 
#ifndef BWL_PINS_H_
#define BWL_PINS_H_

#include <avr/io.h>

#define getbit(port, bit)		((port) & (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}
#define setbit1(port,bit)		{(port)|= (1 << (bit));}
#define setbit0(port,bit)		{(port) &= ~(1 << (bit));}
#define changebit(port,bit)		{(port) ^= (1 << (bit));}
		
#define BIT(p,b)                (b)
#define PORT(p,b)               (PORT ## p)
#define PIN(p,b)                (PIN ## p)
#define DDR(p,b)                (DDR ## p)

#define pin_set_out(io,val)     setbit(PORT(io),BIT(io),val);
#define pin_set_dir(io,dir)     setbit(DDR(io),BIT(io),dir);
#define pin_toggle_out(io)      changebit(PORT(io),BIT(io))

#define pin_get_out(io)			getbit(PORT(io),BIT(io))
#define pin_get_in(io)			getbit(PIN(io),BIT(io))
#define pin_get(io)				getbit(PIN(io),BIT(io))

#define pin_low(io)				setbit1(DDR(io),BIT(io));  setbit0(PORT(io),BIT(io));
#define pin_high(io)			setbit1(DDR(io),BIT(io));  setbit1(PORT(io),BIT(io));
#define pin_input(io)			setbit0(DDR(io),BIT(io));  setbit0(PORT(io),BIT(io));
#define pin_input_pullup(io)	setbit0(DDR(io),BIT(io));  setbit1(PORT(io),BIT(io));

//Example
//#define MYPIN A,1
//
//pin_high(MYPIN);
//pin_input_pullup(MYPIN);
//
//char pin=pin_get(MYPIN)


#endif /* BWL_PINS_H_ */