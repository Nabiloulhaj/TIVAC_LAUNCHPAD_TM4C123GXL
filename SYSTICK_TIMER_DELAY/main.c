#include "TM4C123.h"                    // Device header

/*
	Load = Time_delay * clock_frequency  FORMULA
	Systick control and status register    STCTRL
	Systick reload value register          STRELOAD
	Systick current value register         STCURRENT
*/

uint32_t ms;

void _delay_ms(uint16_t delay)
{
	ms = 0;
	while(delay > ms);

}

int main(void)
{
	SYSCTL->RCGCGPIO =  0x20;  // ENABLE CLOCK FOR PORTF
	//SYSCTL_RCGCGPIO_R = 0x20; // ENABLE CLOCK FOR PORTF
	GPIOF->DEN = 0x0E; // DIGITALISE PF1,PF2,PF3 
	GPIOF->DIR = 0x0E; // PF1,PF2,PF3 AS OUTPUT
	
	// CONFIGURE 4MHz SYSTICK AND ENABLE INTERRUPT SYSTICK 
	SysTick->CTRL = 0x03; 
	
	// SysTick Reload Value = System Clock x Delay Desired 
	// LOAD VALUE FOR 1s
	//SysTick->LOAD = 4000000 - 1; 	
	// LOAD VALUE FOR 500 ms
	// SysTick->LOAD = 2000000 - 1;
	// LOAD VALUE FOR 1 ms
	SysTick->LOAD = 4000 - 1;
	
	while(1)
	{
		GPIOF->DATA ^= (1<<3); // TOGGLE GREEN LED PF3
		_delay_ms(1000); // 1s
	}
}

void SysTick_Handler()
{
	ms++;
}
