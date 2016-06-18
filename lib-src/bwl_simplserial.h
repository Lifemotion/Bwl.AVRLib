#ifndef BWL_GAPUART_H_
#define BWL_GAPUART_H_

typedef unsigned char byte;

byte sserial_devguid[16];
byte sserial_devname[32];
byte sserial_bootname[16];
byte sserial_bootloader_present;
uint16_t sserial_address;

#define CATUART_MAX_PACKET_LENGTH 128

struct
{
	uint16_t		 address_to;
	unsigned	char command;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	int datalength;	
} sserial_request;

struct
{
	unsigned	char result;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	int datalength;
} sserial_response;

//должны быть реализованы
extern void sserial_send_start();
extern void sserial_send_end();
extern void sserial_process_request();
void uart_send( unsigned char);
unsigned char uart_get( void );
unsigned char uart_received( void );

//вызывать
void sserial_poll_uart();
void sserial_send_response();
void sserial_find_bootloader();

#endif /* BWL_GAPUART_H_ */