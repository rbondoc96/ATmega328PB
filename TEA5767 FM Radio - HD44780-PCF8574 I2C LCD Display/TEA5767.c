#include "TEA5767.h"
#include "I2C.h"

void TEA_Init()
{
	I2C_start(TEA_ADDRESS << 1);
	
	I2C_Transmit(0x2C);		//Data Byte 1
	I2C_Transmit(0x98);		//Data Byte 2
	I2C_Transmit(0x10);		//Data Byte 3
	I2C_Transmit(0x10);		//Data Byte 4
	I2C_Transmit(0x40);		//Data Byte 5
	
	I2C_stop();
}

void TEA_change_station(uint32_t station_mhz)
{
	I2C_start(TEA_ADDRESS << 1);
	
	uint8_t byte1, byte2;
	
	switch(station_mhz)
	{
		case 93300000:
			byte1 = 0x2C;
			byte2 = 0x98;
			break;
		case 94100000:
			//byte1 =
			//byte2 =
			break;
		case 95700000:
			//byte1 =
			//byte2 =
			break;
		case 102700000:
			//byte1 =
			//byte2 =
			break;
	}
	
	I2C_Transmit(byte1);	//Set station bytes
	I2C_Transmit(byte2);		
	I2C_Transmit(0x10);		//Output control bytes
	I2C_Transmit(0x10);		
	I2C_Transmit(0x40);		
}

