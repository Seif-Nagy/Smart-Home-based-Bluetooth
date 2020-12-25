/*
 * LCD.h
 *
 *  Created on: 2020
 *      Author: Seif Nagy
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>												/* Include AVR std. library file */
#include <util/delay.h>											/* Include Delay library file */

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* LCD HW Pins */
#define RS 4
#define RW 5
#define E  6
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define HOME 0x02
#define MODE_8BIT 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

void LCD_init(void);
void LCD_sendCommand(unsigned char command);
void LCD_displayCharacter(unsigned char data);
void LCD_displayString(const char *Str);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str);
void LCD_goToRowColumn(unsigned char row,unsigned char col);

#endif /* LCD_H_ */
