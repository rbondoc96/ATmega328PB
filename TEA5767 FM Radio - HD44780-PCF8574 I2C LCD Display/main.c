/*
 * FM Radio and LCD Display.c
 *
 * Created: 11/18/2017 11:57:10 AM
 * Author : Rodrigo
 */ 

#define F_CPU		16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.c"
#include "LCD.c"
#include "TEA5767.c"

uint8_t station_idx = 0;

int main(void)
{
	PCICR |= (1 << PCIE0);		//Turns on Pin change interrupts
	PCMSK0 |= (1 << PCINT7);	//Sets push button interrupt
	
    I2C_Init();
	//TEA_Init();
	LCD_Init();
	
	sei();
	
    while (1) 
    {
		/*
		LCD_setCursor(0, 0);	//Column 0, Line 0
		LCD_Print();			//Ex. "FM 102.7"
		LCD_setCursor(0, 1);	//Column 0, Line 1
		LCD_Print();			//Ex. "102.7 KIIS-FM"
		*/
    }
}

ISR(PCINT0_vect)
{
	//This routine executes twice per button push!
	if(station_idx % 2 == 0)
	{
		TEA_Init(station_mhz[station_idx/2]);
		
		if(station_idx >= 6)
			station_idx = 0;
	}
	station_idx++;
}