/*
 * USART.h
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */

#ifndef USART_H_
#define USART_H_

#define F_CPU 16000000UL					/* Define CPU clock Frequency */
#include <avr/io.h>							/* Include AVR std. library file */
#include <math.h>

#define BAUD_PRESCALE (int)round(((((double)F_CPU / ((double)BAUDRATE * 8.0))) - 1.0))	/* Define prescaler value (Double speed mode) */

void USART_Init(unsigned long);				/* USART initialize function */
char USART_RxChar();						/* Data receiving function */
void USART_TxChar(char);					/* Data transmitting function */
void USART_SendString(char*);				/* Send string of USART data function */

#endif /* USART_H_ */
