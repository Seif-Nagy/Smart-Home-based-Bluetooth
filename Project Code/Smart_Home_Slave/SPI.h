/*
 * SPI.h
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>												/* Include AVR std. library file */
#include <util/delay.h>											/* Include Delay library file */
#include <avr/interrupt.h>										/* Include Interrupt library file */

#define SPIF 7
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))				/* Check if bit is cleared */

void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const unsigned char data);
unsigned char SPI_receiveByte(void);
void SPI_sendString(const unsigned char *Str);
void SPI_receiveString(unsigned char *Str);

#endif /* SPI_H_ */
