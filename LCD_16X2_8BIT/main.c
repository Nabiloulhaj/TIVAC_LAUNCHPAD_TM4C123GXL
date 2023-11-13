#include "TM4C123.h"                    // Device header

/* 
  8 BIT-MODE
	
	RS = PD0
	RW = PD1
	EN = PD2
	
	D0 = PA7
	D1 = PA6
	D2 = PA5
	D3 = PB4
	D4 = PE5
	D5 = PE4
	D6 = PB1
	D7 = PB0	
*/

void delay(long d);
void Printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(char *str);
void set_cursor(unsigned char row,unsigned char pos);
void lcd_init(void);

int main(void)
{
	// ENABLE CLOCK PORTA, PORTB, PORTD, PORTE
	SYSCTL->RCGCGPIO |= (1<<0) | (1<<1) | (1<<3) | (1<<4);
	
	// DIGITALISE PORTS PINS
	GPIOA->DEN |= (1<<5) | (1<<6) | (1<<7);
	GPIOB->DEN |= (1<<0) | (1<<1) | (1<<4);
	GPIOD->DEN |= (1<<0) | (1<<1) | (1<<2);
	GPIOE->DEN |= (1<<4) | (1<<5);
	
	// SET PORT PINS AS OUTPUTS
	GPIOA->DIR |= (1<<5) | (1<<6) | (1<<7);
	GPIOB->DIR |= (1<<0) | (1<<1) | (1<<4);
	GPIOD->DIR |= (1<<0) | (1<<1) | (1<<2);
	GPIOE->DIR |= (1<<4) | (1<<5);
	
	delay(10000);
	
	// INITALISING LCD
	lcd_init();
	set_cursor(0,0);
	lcd_string("Hi!");
	set_cursor(1,0);
	lcd_string("Nabil");

	while(1)
	{
	
	
	}	
	
}

void lcd_data(unsigned char data)
{
	// PASS THE 8-BIT DATA TO THE DATALINES OF LCD
	Printdata(data);
	
	// TURN OFF THE R/W FOR WRITE OPERATION IN LCD
	GPIOD->DATA &= ~(1U<<1);
	
	// TURN ON RS FOR WRITING TO THE DATA REGISTER OF LCD
	GPIOD->DATA |= (1<<0);
	
	// TURN ON EN OF LCD FOR ENABLING THE CLOCK OF LCD
	GPIOD->DATA |= (1<<2);
	
	// WAIT FOR A WHILE
	delay(10000);
	
	// TURN OFF EN OF LCD
	GPIOD->DATA &= ~(1U<<2);
}

void lcd_cmd(unsigned char cmd)
{
	// PASS THE 8-BIT DATA TO THE DATALINES OF LCD
	Printdata(cmd);
	
	// TURN OFF THE R/W FOR WRITE OPERATION IN LCD
	GPIOD->DATA &= ~(1U<<1);
	
	// TURN OFF RS FOR WRITING TO THE DATA REGISTER OF LCD
	GPIOD->DATA &= ~(1U<<0);
	
	// TURN ON EN OF LCD FOR ENABLING THE CLOCK OF LCD
	GPIOD->DATA |= (1<<2);
	
	// WAIT FOR A WHILE
	delay(10000);
	
	// TURN OFF EN OF LCD
	GPIOD->DATA &= ~(1U<<2);
}

void lcd_string(char *str)
{
	while(*str)
	{
		lcd_data(*str);
		str++;
	}

}

void lcd_init(void)
{
	// 8 BIT MODE UTILISING 16 COLUMNS AND 2 ROWS
	lcd_cmd(0x38);
	
	// AUTO-INCREMENTING THE CURSOR WHEN PRINTING THE DATA
	lcd_cmd(0x06);
	
	// CURSOR OFF AND DISPLAY-OFF
	lcd_cmd(0x0C);
	
	// CLEAR SCREEN
	lcd_cmd(0x01);
}

void set_cursor(unsigned char row,unsigned char pos)
{
	if(row == 0 && pos < 16)
	{
		lcd_cmd((pos & 0x0F) | 0x80 );
	}
	else if(row == 1 && pos < 16)
	{
		lcd_cmd((pos & 0x0F) | 0xC0 );
	}
}


void Printdata(unsigned char data) // data = 8 bit hexadecimal data
{
	// D0 = PA7
	if( (data&0x01) == 0x01)
	{ // turn on the pin representing bit zero
		GPIOA->DATA |= (1<<7);
	}
	else
	{ // turn off the pin representing bit zero
		GPIOA->DATA &= ~(1U<<7);
	}
	
	// D1 = PA6
	if( (data&0x02) == 0x02)
	{ // turn on the pin representing bit one
		GPIOA->DATA |= (1<<6);
	}
	else
	{ // turn off the pin representing bit one 
		GPIOA->DATA &= ~(1U<<6);
	}
	
	// D2 = PA5
	if( (data&0x04) == 0x04)
	{ // turn on the pin representing bit two
		GPIOA->DATA |= (1<<5);
	}
	else
	{ // turn off the pin representing bit two 
		GPIOA->DATA &= ~(1U<<5);
	}
	
	// D3 = PB4
	if( (data&0x08) == 0x08)
	{ // turn on the pin representing bit three
		GPIOB->DATA |= (1<<4);
	}
	else
	{ // turn off the pin representing bit three
		GPIOB->DATA &= ~(1U<<4);
	}
	
	// D4 = PE5
	if( (data&0x10) == 0x10)
	{ // turn on the pin representing bit four
		GPIOE->DATA |= (1<<5);
	}
	else
	{ // turn off the pin representing bit four
		GPIOE->DATA &= ~(1U<<5);
  }
	
	// D5 = PE4
	if( (data&0x20) == 0x20)
	{ // turn on the pin representing bit five
		GPIOE->DATA |= (1<<4);
	}
	else
	{ // turn off the pin representing bit five 
		GPIOE->DATA &= ~(1U<<4);
  }
	
	// D6 = PB1
	if( (data&0x40) == 0x40)
	{ // turn on the pin representing bit six  
		GPIOB->DATA |= (1<<1);
	}
	else
	{ // turn off the pin representing bit six 
		GPIOB->DATA &= ~(1U<<1);
	}
	
	// D7 = PB0
	if( (data&0x80) == 0x80) 
	{ // turn on the pin representing bit seven  
		GPIOB->DATA |= (1<<0);
	}
	else
	{ // turn off the pin representing bit seven
		GPIOB->DATA &= ~(1U<<0);
	}
}

void delay(long d)
{
	while(d--);
}
