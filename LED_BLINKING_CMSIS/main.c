
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "TimeDelay.h"


typedef struct{
	uint32_t Dummy[255]; // offset
	uint32_t DATA; // Ox3FC
	uint32_t DIR;
	uint32_t IS;
	uint32_t IBE;
	uint32_t IM;
	uint32_t RIS;
	uint32_t MIS;
	uint32_t ICR;
	uint32_t AFSEL; // 0x420  ==> 0x424
	uint32_t DUMMY1; // FILL THE GAP
	uint32_t DUMMY2; // FILL THE GAP
	uint32_t DUMMY[53]; // FILL THE GAPP
	uint32_t DR2R;
	uint32_t DR4R;
	uint32_t DR8R;
	uint32_t ODR;
	uint32_t PUR;
	uint32_t PDR;
	uint32_t SLR;
	uint32_t DEN;
	uint32_t LOCK;
	uint32_t CR;
	uint32_t AMSEL;
	uint32_t PCTL;
	uint32_t ADCCTL;
	uint32_t DMACTL;
	uint32_t PeriD5;
	uint32_t PeriD6;
	uint32_t PeriD7;
	uint32_t PeriD0;
	uint32_t PeriD1;
	uint32_t PeriD2;
	uint32_t PeriD3;
	uint32_t PrimeCellD0;
	uint32_t PrimeCellD1;
	uint32_t PrimeCellD2;
	uint32_t PrimeCellD3;
	
}GPIO_Registers;

#define GPIOF_BASE 0x40025000UL
#define GPIOF ((GPIO_Registers *)GPIOF_BASE)



int main(void)
{
	SYSCTL_RCGCGPIO_R = 0x20; // ENABLE CLOCK FOR PORTF
	
	//GPIO_PORTF_DEN_R = 0x0E; // PF1,PF2,PF3 AS DIGITAL OUTPUTS
	GPIOF->DEN = 0x0E; // PF1,PF2,PF3 AS DIGITAL OUTPUTS
	
	//GPIO_PORTF_DIR_R = 0x0E; // PF1,PF2,PF3 AS OUTPUT
	GPIOF->DIR = 0x0E; // PF1,PF2,PF3 AS OUTPUT
	
	while(1)
	{
		//GPIO_PORTF_DATA_R |= (1<<3);
		GPIOF->DATA |= (1<<3);
		delay(1000000000);
		
		// GPIO_PORTF_DATA_R &= ~(1<<3);
		GPIOF->DATA &= ~(1<<3);
		delay(1000000000);
	}
}
