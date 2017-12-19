#include "LCD.h"
#include "TEA5767.h"
#include <util/delay.h>
#include <stdio.h>

#ifndef _BV(bit)
#define _BV(bit)	(1 << bit)
#endif

void LCD_Init()
{
	uint8_t *station = station_name[0];
	uint8_t frequency[5];
	sprintf(frequency, "%.1lf", (station_mhz[0] / 1000000.0));		//Converts to a string of format:	Ex. 102700000 = 102.7

	//Set LCD to 4-bit interface, 16x2 lines
	I2C_start(LCD_ADDRESS << 1);

	//Initial Write to LCD is 8-bit mode, sending a couple times
	uint8_t mode = _BV(LCD_FUNCTION_SET) | _BV(LCD_FUNCTION_BIT_MODE);
	I2C_Transmit(mode);
	I2C_Transmit(mode | _BV(LCD_EN));	//Enable toggle for the LCD to receive the data
	I2C_Transmit(mode);
	_delay_us(4992);

	I2C_Transmit(mode | _BV(LCD_EN));
	I2C_Transmit(mode);
	_delay_us(64);

	I2C_Transmit(mode | _BV(LCD_EN));
	I2C_Transmit(mode);
	_delay_us(64);

	//Switching to 4-bit interface and allow LCD commands
	mode &= ~_BV(LCD_FUNCTION_BIT_MODE);	//Switching from 8-bit to 4-bit
	I2C_Transmit(mode);
	I2C_Transmit(mode | _BV(LCD_EN));
	I2C_Transmit(mode);
	_delay_us(64);

	LCD_Command(LCD_FUNCTION_DEFAULT);	//4-bit, 2-line, 5x8 dot display

	LCD_Command(_BV(LCD_ENTRY_MODE) | _BV(LCD_ENTRY_INC));	//Entry mode set,
								//Increments address, shifts cursor to the right at DDRAM write

	LCD_Command(LCD_DISPLAY_ON);	//Turn on display, no cursor, no blink
	LCD_Clear();

	LCD_Line0(station);
	LCD_Line1(frequency);
	I2C_stop();
}

void LCD_Transmit(uint8_t data, uint8_t rs)
{
	I2C_start(LCD_ADDRESS << 1);
	
	uint8_t dataNibble;
	uint8_t ctrlNibble;
	if(rs)	//Sending DATA
	{
		ctrlNibble = _BV(LCD_RS);
	}
	else
	{
		//Sending COMMAND
		ctrlNibble = 0;
	}
	ctrlNibble &= 0x0F;		//Only lower nibble of data packet is the control

	dataNibble = data & 0xF0;	//High data nibble
	I2C_Transmit(dataNibble | ctrlNibble);		//Adding data + control
	I2C_Transmit(dataNibble | (ctrlNibble | (1 << LCD_EN)) );	//Appending ENABLE to the control nibble
	I2C_Transmit(dataNibble | ctrlNibble);

	dataNibble = (data << 4) & 0xF0;			//Low data nibble
	I2C_Transmit(dataNibble | ctrlNibble);
	I2C_Transmit(dataNibble | (ctrlNibble | (1 << LCD_EN)) );	//Appending ENABLE to the control nibble
	I2C_Transmit(dataNibble | ctrlNibble);

	I2C_stop();
	_delay_us(40);		//Execution time stated on the datasheet
}

void LCD_Command(uint8_t cmd)
{
	LCD_Transmit(cmd, 0);
}

void LCD_Data(uint8_t data)
{
	LCD_Transmit(data, 1);
}

void LCD_Put_Char(const uint8_t c)
{
	LCD_Data(c);
}

void LCD_Print(const uint8_t str[])
{
	uint8_t idx = 0;
	while(str[idx])
	{
		LCD_Data(str[idx++]);
	}
}

void LCD_setCursor(uint8_t col, uint8_t row)
{
	//Set DDRAM Address
	uint8_t ddram = _BV(LCD_SET_DDRAM);
	if(row == 0)
	{
		ddram |= _BV(LCD_LINE0_START) + col;	//col from 0 to 0x27 = 39 (decimal)
	}
	else
	{
		ddram |= _BV(LCD_LINE1_START) + col;   //col from 0x40 to 0x67
	}
}

void LCD_Line0(const uint8_t station_name[])
{
	LCD_setCursor(0, 0);

	LCD_Print(station_name);
}

void LCD_Line1(const uint8_t station_mhz[])
{
	LCD_setCursor(0, 1);

	LCD_Print(station_mhz);
}

void LCD_Clear(void)
{
	LCD_Command(_BV(LCD_CLEAR));
	_delay_us(15000);
}
