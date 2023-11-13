#include "TM4C123.h"                    // Device header

void delay(long d)
{
	while(d--);
}


int main(void)
{
	SYSCTL->RCGCGPIO =  0x20;  // ENABLE CLOCK FOR PORTF
	//SYSCTL_RCGCGPIO_R = 0x20; // ENABLE CLOCK FOR PORTF
	
	GPIOF->DEN = 0x0E; // PF1,PF2,PF3 AS DIGITAL OUTPUTS
	
	GPIOF->DIR = 0x0E; // PF1,PF2,PF3 AS OUTPUT
	
	while(1)
	{
		//GPIO_PORTF_DATA_R |= (1<<3);
		GPIOF->DATA |= (1<<3);
		delay(1000000000);
		
		// GPIO_PORTF_DATA_R &= ~(1<<3);
		GPIOF->DATA &= ~(1U<<3);
		delay(1000000000);
	}

}
