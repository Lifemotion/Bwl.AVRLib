/*
 * Bwl ADC lib for AVR: mega48/88/168/328/324/164/2560/1280
 *
 * Author: Nickolay Gusev and others
 * Licensed: open-source Apache license
 *
 * Version: 01.07.2016
 */

#ifndef BWL_HC05_H_
#define BWL_HC05_H_

//��������
//��������� ��������� HC-05, ��������� ����� � ������
//���������� 1, ���� ������������� ������ �������
int  hc_init(char* device_name, char* device_password);
void hc_send_string(char *string);
void hc_send_line(char *string);
void hc_send_int(int val);
void hc_send_long(long val);

//�����������
//�������� ������ � UART-���� HC-05, �������������� ������������������ �� ��������� 9600
void hc_uart_send(char data);
unsigned char hc_uart_get();
unsigned char hc_uart_received();
//���������� ��� KEY � ��������� �����, ������� ������� (isHigh=1) ��� �����, ������ ������� (isHigh=0)
void hc_key_pin_set(char isHigh);
void var_delay_ms(int ms);

#endif /* BWL_HC05_H_ */