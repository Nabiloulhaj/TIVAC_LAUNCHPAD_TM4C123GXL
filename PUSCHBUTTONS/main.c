#include "TM4C123.h"                    // Device header

/*
	PF4 ==> BUTTON SW1 CONNECTED TO GND
	PF0 ==> BUTTON SW2 CONNECTED TO GND & WAKE UP PIN
	PF1 ==> RED LED
	PF2 ==> BLUE LED
	PF3 ==> GREEN LED
*/

/* 
	HOW TO READ VALUE FROM REGISTER:
	
	Var = ( Reg & (1 << BitNumber) ) >> BitNumer;

*/

int main(void)
{
	SYSCTL->RCGCGPIO |= (1<<5); // TURN ON CLOCK FOR PORTF
	
	// WRITING 0x4C4F434B TO LOCK REGISTER UNLOCK WRITING MODE TO THE COMMIT REGISTER CR
	// WRITING ANY OTHER VALUE TO LOCK REGISTER LOCK WRITING MODE TO THE COMMIT REGISTER CR
	// READING FROM LOCK REGISTER RETURNS 1 IF IT'S LOCKED, 0 IF IT'S UNLOCKED
	GPIOF->LOCK = 0x4C4F434B;
	
	// COMMIT REGISTER DETERMINES WHICH BITS OF THR AFSEL, PUR, PDR, DEN, WHEN WRITING TO THIS REGISTERS
	// IF CR IS CLEAREAD BITS OF THR AFSEL, PUR, PDR, DEN, CANNOT BE COMMITED AND STAY CONSERVED TO PREVIOUS VALUE
	// IF CR IS SET BITS OF THR AFSEL, PUR, PDR, DEN, CANN BE COMMITED AND STORE THE NEW VALUE
	
	GPIOF->CR |= (1<<0); // PF0 UNLOCK
	
	GPIOF->DIR |= (1<<3); // PF3 AS OUTPUT GREEN LED
	GPIOF->DIR &= ~( (1U<<4) |(1U<<0) ); // PF4,PF0 AS INPUT BUTTON SW1
	GPIOF->PUR |= (1<<4) | (1<<0); // ENABLE INPUT PULL-RESISTOR PF4, PF0
	GPIOF->DEN |= (1<<3) | (1<<4) | (1<<0); // DIGITALISE PF4, PF3, PF0
	
	
	while(1)
	{
		char Button_State1 = ( (GPIOF->DATA & (1<<4)) >> 4 ); // STATE OF SW BUTTON 1 PF4
		char Button_State2 = ( (GPIOF->DATA & (1<<0)) >> 0 ); // STATE OF SW BUTTON 2 PF0
		
		if(Button_State1 == 0) // SW BUTTON 1 PRESSED
		{
			GPIOF->DATA |= (1<<3); // TURN ON GREEN LED PF3
		}
		if(Button_State2 == 0) // SW BUTTON 2 PRESSED
		{
			GPIOF->DATA &= ~(1u<<3); // TURN OFF GREEN LED PF3
		}
		
		/*
		if(Button_State1 == 0) // SW BUTTON 1 PRESSED
		{
			GPIOF->DATA |= (1<<3); // TURN ON GREEN LED PF3
		}
		else
		{
			GPIOF->DATA &= ~(1U<<3); // TURN OFF GREEN LED PF3
		}
		*/
	}
	
}
