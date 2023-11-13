#include "TM4C123.h"                    // Device header

/*
	PF4 ==> BUTTON SW1 CONNECTED TO GND
	PF0 ==> BUTTON SW2 CONNECTED TO GND & WAKE UP PIN
	PF3 ==> GREEN LED
	
	PA0 ==> U0Rx
	PA1 ==> UOTx
*/

/* 
	HOW TO READ VALUE FROM REGISTER:
	
	Var = ( Reg & (1 << BitNumber) ) >> BitNumer;

*/

int main(void)
{
// ------------ PINS CONFIGURATION ----------------
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
	
// ------------ UART CONFIGURATION ----------------

	// SYSCTL CONFIGURATION
	// ENABLE CLOCK FOR UART PORT USED
	SYSCTL->RCGCUART |= (1<<0);
	
	// ENABLE CLOCK FOR GPIO PORT USED
	SYSCTL->RCGCGPIO |= (1<<0);
	
	// SET ALTERNATE FUNCTION FOR UART PINS HIGH
	GPIOA->AFSEL |= (1<<0) | (1<<1);
	
	// SET THE MODE IN PCTL
	GPIOA->PCTL = 0x11;
	
	// DIGITALISE GPIO PINS OF UART LINE
	GPIOA->DEN |= (1<<0) | (1<<1);
	
	// TURN OFF UART EN & TXEN & RXEN BITS FROM CTL
	UART0->CTL &= ~((1U<<0) | (1U<<8) | (1U<<9));
	
	// SET BAUDRATE IN IBRD & FBRD REGISTER
	// IBRD = UARTSYSCLK / (CLKDIV * BAUD RATE)
	// IBRD = 16000000 / (16 * 9600)
	// IBRD = ( 104 + 0.1666666666667 )
	// IBRD = 104
	// FBRD = (BRDF * 64 + 0.5)
	// FBRD = (0.1666666666667 * 64 + 0.5) = 11.1666... = 11
	UART0->IBRD = 104;
	UART0->FBRD = 11;
	
	// SET WORD LENGHT FOR UART COMMUNICATION IN LCRH 8 BITS
	UART0->LCRH = (1<<5) | (1<<6);
	
	// SELECT CLOCK SOURCE IN CC REGISTER
	UART0->CC = 0x5;
	
	// TURN ON UART EN & TXEN & RXEN BITS FROM CTL
	UART0->CTL |= (1<<0) | (1<<8) | (1<<9);
	
	while(1)
	{
		char Button_State1 = ( (GPIOF->DATA & (1<<4)) >> 4 ); // STATE OF SW BUTTON 1 PF4
		char Button_State2 = ( (GPIOF->DATA & (1<<0)) >> 0 ); // STATE OF SW BUTTON 2 PF0
		
		if(Button_State1 == 0) // SW BUTTON 1 PRESSED
		{
			while( UART0->FR & (1<<5) );
			UART0->DR = 'a';
			GPIOF->DATA |= (1<<3); // TURN ON GREEN LED PF3
			delay(1000000);
		}
		if(Button_State2 == 0) // SW BUTTON 2 PRESSED
		{
			while( UART0->FR & (1<<5) );
			UART0->DR = 'b';
			GPIOF->DATA &= ~(1u<<3); // TURN OFF GREEN LED PF3
			delay(1000000);
		}
		
	}
	
}