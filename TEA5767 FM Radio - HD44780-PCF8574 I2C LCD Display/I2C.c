#include "I2C.h"

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

//Value of Status Register while masking Prescaler bits
#define TWSTAT	TWSR0 & 0xF8

void I2C_Init(void)
{
	//Clears status bits and sets pre-scale = 1
	TWSR0 = 0;
	
	//For a pre-scale of 1 and F_SCL = 100 kHz, TWBRn = 72
	TWBR0 = (F_CPU - (16*F_SCL)) / (2 * F_SCL);
}

uint8_t I2C_Transmit(uint8_t data)
{
	//Send data
	TWDR0 = data;
	TWCR0 = (1 << TWINT)|(1 << TWEN);
	
	//Wait for data to be transmitted
	while(! (TWCR0 & (1 << TWINT)));
	
	//Slave did not send an ACK, error.
	if(TWSTAT != TW_MT_SLA_ACK) { return 1; }
	
	return 0;
}

uint8_t I2C_Receive_ACK(void)
{
	//Generates an ACK on the bus by ACK'ing tranmission
	TWCR0 = (1 << TWINT)|(1 << TWEA)|(1 << TWEN);
	
	//Wait for end of transmission
	while(! (TWCR0 & (1 << TWINT)));	
	
	return TWDR0;
}

uint8_t I2C_Receive_NACK(void)
{
	//Start data reception without ACK'ing
	TWCR0 = (1 << TWINT)|(1 << TWEN);
	
	//Wait for transmission end
	while(! (TWCR0 & (1 << TWINT)));
	
	return TWDR0;
}

uint8_t I2C_start(uint8_t address_rw)
{	
	//TWSTAT is defined as TWSR0 & 0xF8
	
	//Send start condition
	TWCR0 = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
	
	//Wait for transmission to be complete (when TWINT is set)
	while(! (TWCR0 & (1 << TWINT)));
	
	//Executes if START/REP.START has NOT been transmitted
	if((TWSTAT != TW_START) && (TWSTAT != TW_REP_START)) { return 1; }
		
	//Device address into Data Register, then send
	TWDR0 = address_rw;
	TWCR0 = (1<<TWINT)|(1 << TWEN);
	
	//Wait for transmission to complete, and receive ACK/NACK
	while(! (TWCR0 & (1 << TWINT)));
	
	//Only executes if an ACK/NACK was not received.
	if((TWSTAT != TW_MT_SLA_ACK) && (TWSTAT != TW_MR_SLA_ACK)) { return 1; }
		
	return 0;	//Successful operation
}

uint8_t I2C_REP_Start(uint8_t address)
{
	return I2C_start(address);
}

void I2C_stop()
{
	//Send stop condition
	TWCR0 = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);
	
	//Wait for transmission to complete
	while(! (TWCR0 & (1 << TWINT)));
}

