/*
 * slave_main.c
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */

 // AMIT’s Graduation Project 2020 - Smart Home based Bluetooth [Slave]

#include "SPI.h"									/* include SPI header file */
#include "USART.h"									/* Include USART header file */
#include "LCD.h"									/* Include LCD header file */

#define SLAVE_BLUETOOTH								/* Choose which code to be built */

int main(void)
{
#ifdef SLAVE_BLUETOOTH

	DDRA |= ((1<<3) | (1<<2));						// Configure LED ports as output
	SPI_initSlave();								// SPI slave initialize function
	LCD_init();										// LCD initialize function
	SREG |= (1<<7);									// Enable global Interrupt
	SPCR |= (1<<7);									// Enable SPI Interrupt
	LCD_displayString("Enter 1 or 2");				// Display Startup message on LCD
	while(1)
	{}
} 													// End main function
ISR (SPI_STC_vect)									// Interrupt Service Routine (Interrupt code for SPI)
{
	switch (SPI_receiveByte())
		{
		case 0b00000010:
			PORTA ^= (1<<3);						// Toggle LED_1
			LCD_clearScreen();						// Clear LCD screen
			LCD_displayString("LED_1 ON/OFF");		// Display "LED_1 ON/OFF" message
			LCD_displayStringRowColumn(1,0,"Re-Enter 1 or 2");// write in next row and display startup message again
			break;
		case 0b00000100:
			PORTA ^= (1<<2);						// Toggle LED_2
			LCD_clearScreen();						// Clear LCD screen
			LCD_displayString("LED_2 ON/OFF");		// Display "LED_2 ON/OFF" message
			LCD_displayStringRowColumn(1,0,"Re-Enter 1 or 2");// write in next row and display startup message again
			break;
		}
}
#endif
#ifdef SLAVE_BUTTONS

	DDRD |= (1<<3);									// Configure LED_1 port as output
	DDRC |= (1<<2);									// Configure LED_2 port as output
	//PORTD &= ~(1<<3);								// Turn off LED_1
	//PORTC &= ~(1<<2);								// Turn off LED_2
	SPI_initSlave();								// SPI slave initialize function
	SREG |= (1<<7);									// Enable global Interrupt
	SPCR |= (1<<7);									// Enable SPI Interrupt
	while(1)
	{}
} 													// End main function
ISR (SPI_STC_vect)									// Interrupt Service Routine (Interrupt code)
{
	if(SPI_receiveByte() == 0b00000100)
		{
			PORTD ^= (1<<3);
			//PORTD ^= (SPI_receiveByte());			// Toggle LED_1
		}
	else
		{
			PORTC ^= (1<<2);
			//PORTC ^= (SPI_receiveByte());			// Toggle LED_2
		}
}
#endif
