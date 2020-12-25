/*
 * SPI.c
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */
// SPI (Serial  peripheral interface)

#include "SPI.h"

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

void SPI_initMaster(void)
{
	/* Pin Configuration:
	 * SS 'slave select' PB4 --> output
	 * MOSI 'Master o/p slave i/p' PB5 --> output
	 * MISO 'Master i/p slave o/p' PB6 --> input
	 * SCK 'serial clock' PB7 --> output
	 */
	DDRB = ((1<<SS) | (1<<MOSI) | (1<<SCK));
	DDRB &= ~(1<<MISO);
	/* Control Register: SPCR
	 * bit 6: SPI Enable
	 * bit 5: Data order LSB
	 * bit 4: Master Select --> 1
	 * bit 1,0 : Clock Freq. Rate = 64 (with another bit for 2x speed)
	 */
	SPCR = ((1<<6) | (1<<5) | (1<<4) | (1<<1) | (1<<0));

	/* Status Register: SPSR
	 * bit 0: Double speed 2x
	 */
	SPSR |= (1<<0);
}

void SPI_initSlave(void)
{
	/* Pin Configuration:
	 * SS 'slave select' PB4 --> input
	 * MOSI 'Master o/p slave i/p' PB5 --> input
	 * MISO 'Master i/p slave o/p' PB6 --> output
	 * SCK 'serial clock' PB7 --> input
	 */
	DDRB &= ~((1<<SS) | (1<<MOSI) | (1<<SCK));
	DDRB |= (1<<MISO);

	/* Control Register: SPCR
	 * bit 6: SPI Enable
	 * bit 5: Data order LSB
	 * bit 4: Slave Select --> 0
	 * bit 1,0 : Clock Freq. Rate = 64 (with another bit for 2x speed)
	 */
	SPCR = ((1<<6) | (1<<5) | (1<<1) | (1<<0));

	/* Status Register: SPSR
	 * bit 0: Double speed 2x
	 */
	SPSR |= (1<<0);
}

void SPI_sendByte(const unsigned char data)
{
	SPDR = data;  //SPDR --> Data Register
	while(!(SPSR & (1<<7))) //wait until data is sent correctly  {BIT_IS_CLEAR(SPSR,SPIF)}
	{}						//Check if interrupt Flag = 0 then enter while and wait until = 1 then exit while
}

unsigned char SPI_receiveByte(void)
{
	while(!(SPSR & (1<<7))) //wait until data is sent correctly  {BIT_IS_CLEAR(SPSR,SPIF)}
	{}						//Check if interrupt Flag = 0 then enter while and wait until = 1 then exit while
	return SPDR; //SPDR --> Data Register
}

/*void SPI_sendString(const unsigned char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
		i++;
	}
}*/

/*void SPI_receiveString(unsigned char *Str)
{
	unsigned char i = 0;
	Str[i] = SPI_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_receiveByte();
	}
	Str[i] = '\0';
}*/

