/*
 * @file main.c
 *
 * @brief Main source code for the SPI program.
 *
 * This file contains the main entry point and function definitions for the SPI program.
 *
 * @note For more information regarding the SSI module, refer to the
 * Synchronous Serial Interface (SSI) section of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @author
 */

#include "TM4C123GH6PM.h"

#include "SysTick_Delay.h"
#include "SSI0.h"
#include "UART0.h"

int main(void)
{
	SysTick_Delay_Init();
	UART0_Init();
	SSI0_Init();

	while(1)
	{
		//SSI0_Output_Data(0xAA);
		
		
		uint8_t light_level = PMOD_ALS_Read();
		UART0_Output_String("PMOD ALS Data: ");
		UART0_Output_Unsigned_Decimal(light_level);
		UART0_Output_Newline();
		SysTick_Delay1ms(100);
		
	}
}
