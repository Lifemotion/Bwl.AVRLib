#ifndef BWL_TOOLS_H_
#define BWL_TOOLS_H_

//arduino nano mapping
#define AN_D2	0x42 //PORTD2
#define AN_D3	0x43 //PORTD3
#define AN_D4	0x44 //PORTD4
#define AN_D5	0x45 //PORTD5
#define AN_D6	0x46 //PORTD6
#define AN_D7	0x47 //PORTD7
#define AN_D8	0x20 //PORTB0
#define AN_D9	0x21 //PORTB1
#define AN_D10	0x22 //PORTB2
#define AN_D11	0x23 //PORTB3
#define AN_D12	0x24 //PORTB4
#define AN_D13	0x25 //PORTB5

#define AN_A0	0x30 //PORTC0
#define AN_A1	0x31 //PORTC1
#define AN_A2	0x32 //PORTC2
#define AN_A3	0x33 //PORTC3
#define AN_A4	0x34 //PORTC4
#define AN_A5	0x35 //PORTC5

#define bit_set(var, bit)		((var) |= (uint8_t)(1<<bit))
#define bit_clr(var, bit)		((var) &= (uint8_t)~(1<<bit))
#define bit_toggle(var, bit)	((var) ^= (uint8_t)(1<<bit))
#define bit_read(var, bit)		((var) &  (uint8_t)(1<<bit))

#define sbi(port, bit)			(port) |=  (1 << (bit))
#define cbi(port, bit)			(port) &= ~(1 << (bit))
#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

//pin operations by number PORTA0=0x10, PORTA7=0x17, PORTB0=0x20 etc
void set_pin_zero(unsigned char pin);
void set_pin_one(unsigned char pin);
void set_pin_output(unsigned char pin, unsigned char enable);
void set_pin_direction(unsigned char pin, unsigned char is_output);
unsigned char get_pin(unsigned char pin);

#endif /* BWL_UART_H_ */

