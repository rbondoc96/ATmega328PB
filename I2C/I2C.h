#ifndef I2C_H
#define I2C_H

#include <util/twi.h>

#define F_SCL	100000	//100 kHz SCL Frequency

//Initializes the I2C/TWI interface with TWI0
void I2C_Init(void);

/*************************************************************************                                                                    
 Transmits a BYTE of data via I2C to a PREVIOUSLY ADDRESSED device.
 
 Parameters:	byte to be sent
 Returns:		0	success
				1	fail
************************************************************************/
uint8_t I2C_Transmit(uint8_t data);

/*

 */
uint8_t I2C_Receive_ACK(void);
uint8_t I2C_Receive_NACK(void);

/*************************************************************************                                                                    
 These functions send a start condition to a specified device address
 
 Parameters:	byte to be sent
 Returns:		0	access successful
				1	failed
************************************************************************/
uint8_t I2C_start(uint8_t address);
uint8_t I2C_REP_Start(uint8_t address);

//Stops data transfer and releases SDA line
void I2C_stop();

#endif