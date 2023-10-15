#include "TM4C123.h"                    // Device header

/* WE WILL USE ROW SCANING TECHNIQUE
	R1 --> PB3  OUTPUT
	R2 --> PC4  OUTPUT
	R3 --> PC5  OUTPUT
	R4 --> PC6  OUTPUT
	
	C1 --> PC7  INPUT_PULL_UP_RES
	C2 --> PD6	INPUT_PULL_UP_RES
	C3 --> PD7  INPUT_PULL_UP_RES // SPECIAL PIN WHICH MEANS WE NEED TO WORK WITH THE LOCK REGISTER
*/

uint8_t number;
void delay(long d);


int main(void)
{
	// ENABLE CLOCK FOR PORTB, PORTC, PORTD
	SYSCTL->RCGCGPIO |= (1<<1) | (1<<2) | (1<<3);
	
	// PD7 SPECIAL PIN --> LOCK REGISTER & COMMIT REGISTER
	// UNLOCK KEY FOR PD7
	GPIOD->LOCK = 0x4C4F434B;
	
	// ENABLE WRITTING FOR PD7 COMMIT REGISTER CR
	GPIOD->CR |= (1<<7);
	
	// DIGITALISE THE PINS
	GPIOB->DEN |= (1<<3);
	GPIOC->DEN |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	GPIOD->DEN |= (1<<6) | (1<<7);
	
	// CONFIGURE OUTPUT PINS
	GPIOB->DIR |= (1<<3);
	GPIOC->DIR |= (1<<4) | (1<<5) | (1<<6);
	
	// CONFIGURE INPUT PINS
	GPIOC->DIR &= ~(1U<<7);
	GPIOD->DIR &= ~((1U<<6) | (1U<<7));
	
	// ENABLE PULL-UP RESISTOR
	GPIOC->PUR |= (1<<6);
	GPIOD->PUR |= (1<<6) | (1<<7);
	
	

	while(1)
	{
		// ------------- ROW 1 ------------------
		GPIOB->DATA &= ~(1U<<3);
		GPIOC->DATA |= (1<<4) | (1<<5) | (1<<6); 
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number =1;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number =2;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number =3;
			delay(50000);
		}
		
		// ------------- ROW 2 ------------------
		GPIOC->DATA &= ~(1U<<4);
		GPIOB->DATA |= (1<<3);
		GPIOC->DATA |= (1<<5) | (1<<6); 
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number =4;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number =5;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number =6;
			delay(50000);
		}
		
		// ------------- ROW 3 ------------------
		GPIOC->DATA &= ~(1U<<5);
		GPIOB->DATA |= (1<<3);
		GPIOC->DATA |= (1<<4) | (1<<6); 
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number =7;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number =8;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number =9;
			delay(50000);
		}
		
		// ------------- ROW 4 ------------------
		GPIOC->DATA &= ~(1U<<6);
		GPIOB->DATA |= (1<<3);
		GPIOC->DATA |= (1<<4) | (1<<5); 
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number ='*';
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number =0;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number ='#';
			delay(50000);
		}
		
		
	}

}

void delay(long d)
{
	while(d--);
}
