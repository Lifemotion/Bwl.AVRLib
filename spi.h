//Библиотека аппаратного SPI для контроллеров ATMEGAx8
#ifndef SPI_H
#define SPI_H

#define SPI_DDRX	DDRB
#define SPI_PORTX	PORTB
#define SPI_SS		PB2
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5

#include <stdint.h>

//инициализация SPI модуля
void spi_init(void);
//выбрать чип
void spi_unselect(void);
//снять выбор чипа
void spi_select(void);
//отправить байт данных по SPI
void spi_write(uint8_t data);
//отправить и получить байт данных по SPI
uint8_t spi_read(uint8_t data);
//отправить несколько байт данных по SPI
void spi_write_array(uint8_t num, uint8_t *data);
//отправить и получить несколько байт данных по SPI
void spi_read_array(uint8_t num, uint8_t *data);


#ifndef SPI_DDRX
#warning "Define SPI_DDRX!"
#define SPI_DDRX	DDRB
#endif

#ifndef SPI_PORTX
#warning "Define SPI_PORTX!"
#define SPI_PORTX	PORTB
#endif

#ifndef SPI_SS
#warning "Define SPI_SS!"
#define SPI_SS	PB2
#endif

#ifndef SPI_MOSI
#warning "Define SPI_MOSI!"
#define SPI_MOSI	PB3
#endif

#ifndef SPI_MISO
#warning "Define SPI_MISO!"
#define SPI_MISO	PB4
#endif

#ifndef SPI_SCK
#warning "Define SPI_SCK!"
#define SPI_SCK		PB5
#endif

#endif //SPI_H