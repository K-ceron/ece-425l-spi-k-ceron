/**
 * @file SSI0.c
 *
 * @brief Source code for the SSI0 driver.
 *
 * This file contains the function definitions for the SSI0 driver.
 *
 * @note For more information regarding the SSI module, refer to the
 * Synchronous Serial Interface (SSI) section of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the system clock (50 MHz) is used.
 *
 * @author
 */

#include "SSI0.h"

void SSI0_Init(void)
{
	//Enable the clock to the SSI0 module by setting the
	//R0 bit (BIT 0) in the RCGCSSI register
	SYSCTL -> RCGCSSI |= 0x01;
	
	//Enable the clock to Port A by setting the
	//R0 bit (Bit 0) in the RCGCGPIO register
	SYSCTL -> RCGCGPIO |= 0x01;
	
	//Configure the PA2 (SCLK), PA3 (CS), PA4 (MISO) and PA5 (MOSI) pins to use the alternate function
	// by setting Bits5 to 2 in the AFSEL register
	GPIOA -> AFSEL |= 0x3C;
	
	//clear the PMC2, PMC3, PMC4, and PMC5 fields in te PCTL register before configuration
	GPIOA -> PCTL &= ~0x00FFFF00; 
	
	//Configure the PA5 to PA2 pins to operate as SSI pins by writing 0x2 to te 
	// corresponding PMCn fields in the PCTL register.
	// The 0x2 value is derived from TABLE 15-1 in te TM4C123G Microcontroller Datsheet
	GPIOA -> PCTL |= 0x00222200; 
	
	// Enable he digital functionality for the PA5 to PA2 pins
	// by setting Bits 5 to 2 in the DEN register
	GPIOA-> DEN |= 0x3C;
	
	//Disable the SSI0 module before configuarion by clearing
	// the SSE bit (bit 1) in the CR1 register
	SSI0 -> CR1 &= ~0x02;
	
	//PRELAB
	
	SSI0 -> CR1 &= ~0x01;
	
	
	SSI0 -> CR1 &= ~0x04;

	SSI0 -> CC &= ~0xF;
	
	SSI0 -> CPSR = 50;
	SSI0 -> CR0 &= ~0xFF00;
	
	
	
	 //Task Set SPO=1 AND SPH =1
  SSI0->CR0 |= 0x00C0; 
	
	
	 // 16-bit data
    SSI0->CR0 |= 0x000F;
		
	
	
	 
	//SSI0 -> CR0 &= ~0x0080;
	
	//SSI0 -> CR0 &= ~0x0040;
	
	SSI0 -> CR0 &= ~0x0030;
	
	//SSI0 -> CR0 |= 0x0007;
	
	SSI0 -> CR1 |= 0x02;
	
	
	
	
}

uint16_t SSI0_Input_Data(void)
{
	//Wait until the RX FIFO is not empty and then read the data
	
	
	while((SSI0->SR & SSI0_RX_FIFO_NOT_EMPTY_BIT_MASK) == 0);
	
	 
   
	
	
	//return (uint8_t)(SSI0->DR & 0xFF);
	return	(uint16_t)(SSI0->DR);
}

void SSI0_Output_Data(uint16_t data)
{
	//Wait until the TX FIFO is empty and then transmit the data
//	while((SSI0->SR & SSI0_TX_FIFO_EMPTY_BIT_MASK) == 0);
	//SSI0->DR = data;
	
	
	   while((SSI0->SR & 0x02) == 0); // wait until TFE = 1
    SSI0->DR = data;
	
}


uint8_t PMOD_ALS_Read(void)
{

    SSI0_Output_Data(0xAAAA);  
		
		uint16_t pmod_als_raw_data = SSI0_Input_Data();
	
		uint8_t light_level = (pmod_als_raw_data >> 5) & 0xFF;
		

    return light_level; 
}
