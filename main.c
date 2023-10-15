/* 7 SEGMENT DISPLAY CC */

/* 
	a ==> PA7 ==> 0
	b ==> PA6 ==> 1
	c ==>	PA5 ==> 2
	d ==> PB4 ==> 3
	e ==> PE5 ==> 4
	f ==> PE4 ==> 5
	g ==> PB1 ==> 6
	h/dp ==> PB0 ==> 7
*/

#include "TM4C123.h"                    // Device header

void delay(long d);
void Printdata(unsigned char data);

// COMMON CATODE 7-SEGMENT DISPLAY VALUES NUMBERS 0-9
 char bcd_numbers[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};

int main(void)
{
	// ENABLE CLOCK OF GPIOA, GPIOB, GPIOE
	SYSCTL->RCGCGPIO |= (1<<0) | (1<<1) | (1<<4); 
	
	// DIGITALISE EACH PIN USED IN USED PORT
	GPIOA->DEN |= (1<<7) | (1<<6) | (1<<5);
	GPIOB->DEN |= (1<<4) | (1<<1) | (1<<0);
	GPIOE->DEN |= (1<<5) | (1<<4);
	
	// SET EACH PIN USED AS OUTPUT
	GPIOA->DIR |= (1<<7) | (1<<6) | (1<<5);
	GPIOB->DIR |= (1<<4) | (1<<1) | (1<<0);
	GPIOE->DIR |= (1<<5) | (1<<4);
	
	
	while(1)
	{
		Printdata(bcd_numbers[0]);
		delay(100000000);
		Printdata(bcd_numbers[1]);
		delay(100000000);
		Printdata(bcd_numbers[2]);
		delay(100000000);
		Printdata(bcd_numbers[3]);
		delay(100000000);
		Printdata(bcd_numbers[4]);
		delay(100000000);
		Printdata(bcd_numbers[5]);
		delay(100000000);
		Printdata(bcd_numbers[6]);
		delay(100000000);
		Printdata(bcd_numbers[7]);
		delay(100000000);
		Printdata(bcd_numbers[8]);
		delay(100000000);
		Printdata(bcd_numbers[9]);
		delay(100000000);
	}
}

void delay(long d)
{
	while(d--);
}



void Printdata(unsigned char data) // data = 8 bit hexadecimal data
{
	// BIT 0 , a ==> PA7 ==> 0
	if( (data&0x01) == 0x01)
	{ // turn on the pin representing bit zero
		GPIOA->DATA |= (1<<7);
	}
	else
	{ // turn off the pin representing bit zero
		GPIOA->DATA &= ~(1U<<7);
	}
	
	// BIT 1 , b ==> PA6 ==> 1
	if( (data&0x02) == 0x02)
	{ // turn on the pin representing bit one
		GPIOA->DATA |= (1<<6);
	}
	else
	{ // turn off the pin representing bit one 
		GPIOA->DATA &= ~(1U<<6);
	}
	
	// BIT 2 , c ==>	PA5 ==> 2
	if( (data&0x04) == 0x04)
	{ // turn on the pin representing bit two
		GPIOA->DATA |= (1<<5);
	}
	else
	{ // turn off the pin representing bit two 
		GPIOA->DATA &= ~(1U<<5);
	}
	
	// BIT 3 , d ==> PB4 ==> 3
	if( (data&0x08) == 0x08)
	{ // turn on the pin representing bit three
		GPIOB->DATA |= (1<<4);
	}
	else
	{ // turn off the pin representing bit three
		GPIOB->DATA &= ~(1U<<4);
	}
	
	// BIT 4 , e ==> PE5 ==> 4
	if( (data&0x10) == 0x10)
	{ // turn on the pin representing bit four
		GPIOE->DATA |= (1<<5);
	}
	else
	{ // turn off the pin representing bit four
		GPIOE->DATA &= ~(1U<<5);
  }
	
	// BIT 5 , f ==> PE4 ==> 5
	if( (data&0x20) == 0x20)
	{ // turn on the pin representing bit five
		GPIOE->DATA |= (1<<4);
	}
	else
	{ // turn off the pin representing bit five 
		GPIOE->DATA &= ~(1U<<4);
  }
	
	// BIT 6 , g ==> PB1 ==> 6
	if( (data&0x40) == 0x40)
	{ // turn on the pin representing bit six  
		GPIOB->DATA |= (1<<1);
	}
	else
	{ // turn off the pin representing bit six 
		GPIOB->DATA &= ~(1U<<1);
	}
	
	// BIT 7 , h/dp ==> PB0 ==> 7
	if( (data&0x80) == 0x80) 
	{ // turn on the pin representing bit seven  
		GPIOB->DATA |= (1<<0);
	}
	else
	{ // turn off the pin representing bit seven
		GPIOB->DATA &= ~(1U<<0);
	}
}
