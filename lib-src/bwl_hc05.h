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

//вызывать
//процедура настройки HC-05, установка имени и пароля
//возвращает 1, если инициализация прошла успешно
int  hc_init(char* device_name, char* device_password);
void hc_send_string(char *string);
void hc_send_line(char *string);
void hc_send_int(int val);
void hc_send_long(long val);

//реализовать
//отправка данных в UART-порт HC-05, предварительно инициализированный со скоростью 9600
void hc_uart_send(char data);
unsigned char hc_uart_get();
unsigned char hc_uart_received();
//установить пин KEY в состояние выход, высокий уровень (isHigh=1) или выход, низкий уровень (isHigh=0)
void hc_key_pin_set(char isHigh);
void var_delay_ms(int ms);

#endif /* BWL_HC05_H_ */