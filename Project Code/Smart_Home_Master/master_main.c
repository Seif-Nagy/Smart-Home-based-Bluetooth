/*
 * master_main.c
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */

 // AMIT’s Graduation Project 2020 - Smart Home based Bluetooth [Master]

#include "SPI.h"									/* include SPI header file */
#include "USART.h"									/* Include USART header file */

#define MASTER_BLUETOOTH							/* Choose which code to be built */

int main(void)
{
#ifdef MASTER_BLUETOOTH

	SPI_initMaster();								// SPI master initialize function
	USART_Init(9600); 								// initialize USART with 9600 baud rate
	char Data_in;
	_delay_ms(30);									// delay until Slave function is initialized in Slave ECU
	while(1)
	{
		Data_in = USART_RxChar();	 				// Receive data from Bluetooth device
		if(Data_in == '1')
		{
			SPI_sendByte(0b00000010);				// Send to Slave to turn on/off LED_1
			USART_SendString("LED_1 ON/OFF \n");	// Send status of LED_1 to Bluetooth receiver/transmitter
		}
		else if (Data_in == '2')
		{
			SPI_sendByte(0b00000100);				// Send to Slave to turn on/off LED_2
			USART_SendString("LED_2 ON/OFF \n");	// Send status of LED_2 to Bluetooth receiver/transmitter
		}
	}
}
#endif
#ifdef MASTER_BUTTONS

	SPI_initMaster();								// SPI master initialize function
	DDRD  &= ~(1<<4 | (1<<5));						// Configure Button Ports as input
	_delay_ms(30);									// delay until Slave function is initialized in Slave ECU
	while(1)
	{
		if(PIND & (1<<4))
		{
			SPI_sendByte(0b00000100);				// Send to Slave to turn on/off LED_1
			while(PIND & (1<<4));					// Wait until pressed button is released
		}
		else if(PIND & (1<<5))
		{
			SPI_sendByte(0b00001000);				// Send to Slave to turn on/off LED_2
			while( PIND & (1<<5));					// Wait until pressed button is released
		}
	}
}
#endif
