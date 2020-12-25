/*
 * LCD.c
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */
// LCD

#include "LCD.h"

//LCD_sendCommand(CURSOR_ON); //CURSOR ON (0x0E), (before writing in LCD)

void LCD_init(void)
{
	LCD_DATA_PORT_DIR = 0xFF; 								// DEFINE OUTPUT
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); 		// DEFINE OUTPUT for RS/RW/ENABLE
	LCD_sendCommand(HOME);									// Return home
	LCD_sendCommand(MODE_8BIT); 							// 8 bit mode
	LCD_sendCommand(CURSOR_OFF); 							// Cursor off (0x0C)
	LCD_sendCommand(CLEAR_COMMAND); 						// Clear screen
}

void LCD_sendCommand(unsigned char command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); 							/* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); 							/* write data to LCD so RW=0 */
	LCD_DATA_PORT = command; 								/* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); 											/* delay for processing Tdsw = 100ns */
	SET_BIT(LCD_CTRL_PORT,E); 								/* Enable LCD E=1 */
	_delay_ms(1); 											/* delay for processing Tpw - Tdws = 190ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);								/* disable LCD E=0 */
	_delay_ms(1); 											/* delay for processing Th = 13ns */
}

void LCD_displayCharacter(unsigned char data)
{
	SET_BIT(LCD_CTRL_PORT,RS); 								/* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); 							/* write data to LCD so RW=0 */
	SET_BIT(LCD_CTRL_PORT,E);								/* Enable LCD E=1 */
	_delay_ms(1);											/* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT = data;									/* out the required data char to the data bus D0 --> D7 */
	_delay_ms(1); 											/* delay for processing Tdsw = 100ns */
	SET_BIT(LCD_CTRL_PORT,E);								/* Enable LCD E=1 */
	_delay_ms(1); 											/* delay for processing Tpw - Tdws = 190ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); 							/* disable LCD E=0 */
	_delay_ms(1); 											/* delay for processing Th = 13ns */
}

void LCD_displayString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(unsigned char row,unsigned char col)
{
	unsigned char Address;									/* calculate the required address */
	switch(row)												/* ADDRESS = COL+(0X40*ROW) */
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;

	}
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str)
{
	LCD_goToRowColumn(row,col); 							/* go to to the required LCD position */
	LCD_displayString(Str); 								/* display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); 						//clear screen
}
