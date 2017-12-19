#ifndef TEA5767_H
#define TEA5767_H

#define TEA_ADDRESS	0x60	//110 0000b

uint32_t station_mhz[] = {93300000, 94100000, 95700000, 102700000};
const uint8_t *station_name[4] = {"Channel 93.3", "Star 94.1", "JAM'N 95.7", "102.7 KIIS-FM"};

/************************************************************************
	Initializes the TEA5767. 93.3 is the first station played. 
	
	Function is called AFTER I2C_start(TEA_ADDRESS) in main.c
*************************************************************************/
void TEA_Init();

/************************************************************************
	Changes the station the TEA is connected to the the parameter passed
	to the function
	
	Parameters:		station_mhz		Station to connect (full MHz value)
*************************************************************************/
void TEA_change_station(uint32_t station_mhz);

#endif