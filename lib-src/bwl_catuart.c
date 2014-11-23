#include <avr/io.h>
#include "bwl_catuart.h"

#define CATUART_ADDITIONAL 8
unsigned char cuRecvData[CATUART_MAX_PACKET_LENGTH+CATUART_ADDITIONAL];
unsigned char cuRecvDataPointer;

const unsigned char crc8table[256]={0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65, 157,
	195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220, 35,125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98, 190,
	224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255, 70,24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7, 219,
	133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154, 101, 59,217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36, 248, 166,
	68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185, 140, 210,48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205, 17, 79,
	173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80, 175, 241, 19,77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238, 50, 108, 142, 208, 83,
	13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115, 202, 148, 118, 40, 171, 245, 23,73, 8, 86, 180, 234, 105, 55, 213, 139, 87, 9, 235, 181, 54, 104, 138, 212, 149,
203, 41, 119, 244, 170, 72, 22, 233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168, 116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53};

unsigned char crc8data;
unsigned const char mask=127;

void crc8(unsigned char data)
{
	crc8data=crc8table[crc8data^data];
}

void catuart_send_response_universal_crc8 (byte typecode, byte crcstart, byte datalength, bool fixedlength)
{
	catuart_tx_on();
	cuResponse.type=typecode;
	uart_send(0);
	uart_send(0);
	uart_send(0xFD);
	uart_send(cuAddress[0]&mask);
	uart_send(cuAddress[1]&mask);
	uart_send(cuAddress[2]&mask);
	uart_send(cuResponse.type);
	uart_send(cuResponse.answer&mask);
	
	crc8data=crcstart;
	crc8(cuAddress[0]&mask);
	crc8(cuAddress[1]&mask);
	crc8(cuAddress[2]&mask);
	crc8(cuResponse.type);
	crc8(cuResponse.answer&mask);
	
	if (datalength>CATUART_MAX_PACKET_LENGTH){datalength=CATUART_MAX_PACKET_LENGTH;}
	if (!fixedlength)
	{
		uart_send(datalength);
		crc8(datalength);
	}
	for (byte i=0; i< datalength; i++)
	{
		uart_send(cuResponse.data[i]&mask);
		crc8(cuResponse.data[i]&mask);
	}
	uart_send(crc8data&mask);
	uart_send(0xFB);
	uart_send(0);
	uart_send(0);
	catuart_tx_off();
}

void catuart_send_response_type01 ()
{
	catuart_send_response_universal_crc8(1,0xAA,cuResponse.datalength,false);
}

void catuart_send_response_type08 ()
{
	catuart_send_response_universal_crc8(8,0xAA,4,true);
}

void catuart_send_response_type10 ()
{
	catuart_send_response_universal_crc8(10,0xAA,8,true);
}

void catuart_send_response (unsigned char type)
{
	if (type==0){catuart_send_response_type01();}	
	if (type==8){catuart_send_response_type08();}
	if (type==10){catuart_send_response_type10();}
}

char catuart_process_internal()
{
	if (cuRequest.command==120)
	{
		cuResponse.answer=121;
		cuResponse.data[0]=cuDeviceFamily[0];
		cuResponse.data[1]=cuDeviceFamily[1];
		cuResponse.data[2]=cuDeviceModel;
		cuResponse.data[3]=cuDeviceVersion;
		catuart_send_response_type08(cuResponse);
		return 1;
	}
	if (cuRequest.command==122)
	{
		cuResponse.answer=123;
		cuResponse.data[0]=cuRequest.data[0]+1;
		cuResponse.data[1]=cuRequest.data[1]+1;
		cuResponse.data[2]=cuRequest.data[2]+1;
		cuResponse.data[3]=cuRequest.data[3]+1;
		cuResponse.data[4]=cuRequest.data[4]+1;
		cuResponse.data[5]=cuRequest.data[5]+1;
		cuResponse.data[6]=cuRequest.data[6]+1;
		cuResponse.data[7]=cuRequest.data[7]+1;
		catuart_send_response_type10(cuResponse);
		return 1;
	}
	if (cuRequest.command==124)
	{
		unsigned long myAddr;
		unsigned long reqAddr;
		myAddr=((long)(cuAddress[0])<<14)+((long)(cuAddress[1])<<7)+((long)(cuAddress[2]));
		reqAddr=((long)(cuRequest.data[0])<<14)+((long)(cuRequest.data[1])<<7)+((long)(cuRequest.data[2]));
		myAddr++;
		reqAddr++;
		if (reqAddr>myAddr)
		{
			cuResponse.answer=125;
			cuResponse.data[0]=0;
			cuResponse.data[1]=0;
			catuart_send_response_type08(cuResponse);
			return 1;
		}
	}
	
	return 0;
}

byte process_packet_universal_crc8(byte crcstart, byte datalength, bool fixedlength)
{
	cuRequest.command=cuRecvData[4];
	byte offset=5;
	
	if (!fixedlength)							{datalength=cuRecvData[5]; offset+=1;}
	if (datalength>CATUART_MAX_PACKET_LENGTH)	{datalength=CATUART_MAX_PACKET_LENGTH;}
	cuRequest.datalength=datalength;
	
	for (byte i=0; i< datalength; i++)
	{
		cuRequest.data[i]=cuRecvData[offset+i];
	}
	
	byte crc1=cuRecvData[offset+datalength];
	crc8data=crcstart;
	for (unsigned char i=0; i<offset+datalength; i++)
	{
		crc8(cuRecvData[i]);
	}
	crc8data&=mask;
	if ((crc1==crc8data)&&(cuRecvDataPointer==offset+datalength+2)){	return 1;}
		
	return 0;
}

void catuart_poll_uart()
{
	catuart_tx_off();
	byte read=uart_peek();
	if (read<0xFF)
	{
		if (cuRecvDataPointer<CATUART_MAX_PACKET_LENGTH+CATUART_ADDITIONAL)
		{
			cuRecvData[cuRecvDataPointer]=read;
			cuRecvDataPointer++;
		};
		if (read==0xFE)	{cuRecvDataPointer=0;}
		if (read==0xFC)
		{
			if(( (cuRecvData[0]==0)&&(cuRecvData[1]==0)&&(cuRecvData[2]==0)) ||((cuRecvData[0]==cuAddress[0])&&(cuRecvData[1]==cuAddress[1])&&(cuRecvData[2]==cuAddress[2])))
			{
				cuRequest.address[0]=cuRecvData[0];
				cuRequest.address[1]=cuRecvData[1];
				cuRequest.address[2]=cuRecvData[2];
				cuRequest.type=cuRecvData[3];
				byte processed=0;
				if (cuRequest.type==0x08)	{processed=process_packet_universal_crc8(0xAA,4,true);}
				if (cuRequest.type==0x10)	{processed=process_packet_universal_crc8(0xAA,8,true);}
				if (cuRequest.type==10)		{processed=process_packet_universal_crc8(0xAA,8,true);}	
				if (cuRequest.type==0x05)	{processed=process_packet_universal_crc8(0xAA,0,true);}	
				if (cuRequest.type==0x01)	{processed=process_packet_universal_crc8(0xAA,0,false);}		
				if (processed==1)
				{
					if (catuart_process_internal()==0){	catuart_process_request();}
				}
			}
		}
	}
}