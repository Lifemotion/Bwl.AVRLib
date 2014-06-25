#ifndef BWL_GAPUART_H_
#define BWL_GAPUART_H_

#include "stdbool.h"

unsigned char cuAddress[3];
unsigned char cuDeviceFamily[2];
unsigned char cuDeviceModel;
unsigned char cuDeviceVersion;

typedef unsigned char byte;
#define CATUART_MAX_PACKET_LENGTH 38

struct
{
	unsigned	char address[3];
	unsigned	char command;
	unsigned	char type;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	char datalength;	
} cuRequest;

struct
{
	unsigned	char answer;
	unsigned	char type;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	char datalength;
} cuResponse;

//должны быть реализованы
extern void catuart_tx_on();
extern void catuart_tx_off();
extern void catuart_process_request();
void uart_send( unsigned char);
unsigned char uart_peek( void );

//вызывать
void catuart_poll_uart();
void catuart_send_response (unsigned char type);

#endif /* BWL_GAPUART_H_ */