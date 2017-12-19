#ifndef LCD_H
#define LCD_H

#define LCD_ADDRESS	0x27

/*	List of LCD Command bit positions	*/
#define LCD_CLEAR	0
#define LCD_HOME	1
#define LCD_ENTRY_MODE	2
	#define LCD_ENTRY_INC	1
	#define LCD_ENTRY_SHIFT	1
#define LCD_DISPLAY	3
	#define LCD_DISPLAY_ON	0x0C	//Command Bytes, cursor off, blink off
	#define LCD_DISPLAY_OFF	0x08
#define LCD_CURSOR	4
#define LCD_FUNCTION_SET	5				//Bit positions below
	#define LCD_FUNCTION_BIT_MODE	4	//1 - 8 bit		0 - 4-bit
	#define LCD_FUNCTION_LINE_MODE	3	//1 - 2 lines	0 - 1 line
	#define LCD_FUNCTION_DOT_MODE	2	//1 - 5x10		0 - 5x8 
	#define LCD_FUNCTION_DEFAULT	0x28	//Default command byte, 4bit, 2 lines, 5x8 dot digits
											//Can't display 5x10 digits on 2 line display
#define LCD_SET_CGRAM	6
#define LCD_SET_DDRAM	7
#define LCD_BUSY		7

/*	DDRAM Register positions for display	*/
#define LCD_LINE0_START	0x00		//DDRAM address for start of Line 0
#define LCD_LINE1_START	0x40		//DDRAM address for start of Line 1


/*	4 Bit Data Bit Positions for LCD (High Nibble positions)	*/
#define LCD_DATA_3	7
#define LCD_DATA_2	6
#define LCD_DATA_1	5	
#define LCD_DATA_0	4

/*	Pin-outs for RS, RW, E on PCF8574	*/
#define	LCD_RS	0		
#define LCD_RW	1
#define LCD_EN	2

/************************************************************************
	Initializes the LCD to output the first station, 93.3
*************************************************************************/
void LCD_Init(void);

/************************************************************************
	This family of functions transmits either a command or data to the
	PCF8574 that interfaces with the HD44780 LCD. 
	
	The connection of this device only allows 4 DATA bits to the data
	register of the LCD at a time, but its control bits can still be
	accessed, as the PCF receives 8 bit data from the master.
	
	Parameters:	data	8 byte data or command
				rs		0	command being sent
						1   data being sent                                                              
*************************************************************************/
void LCD_Transmit(uint8_t data, uint8_t rs);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);

/************************************************************************
                                                                   
*************************************************************************/
void LCD_Put_Char(const uint8_t c);
void LCD_Print(const uint8_t str[]);



/************************************************************************
                                                                   
*************************************************************************/
void LCD_setCursor(uint8_t col, uint8_t line);
void LCD_Line0(const uint8_t station_name[]);
void LCD_Line1(const uint8_t station_mhz[]);

void LCD_Clear(void);

#endif