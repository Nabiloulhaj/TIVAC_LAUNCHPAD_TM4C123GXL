#include "TM4C123.h"                    // Device header

/*
		WE HAVE 2 PWM MODULE, EACH PWM MODULE HAS 8 CHANNEL.
		WE WILL USE PWM1 --> CHANNEL6 --> PF2
*/


void delay(long d);
uint16_t i;

int main(void)
{
	
// -------- CLOCK SETTING FOR PWM AND GPIODF PORT ---------
	// ENABLE CLOCK FOR PWM1 : RCGCPWM REGISTER
	SYSCTL->RCGCPWM |= (1<<1);
	
	// ENABLE CLOCK FOR PORTF
	SYSCTL->RCGCGPIO |= (1<<5);
	
	// DIRECTLY FEED CLOCK TO PWM1 WITHOUT PRE-DIVIDER : RCC REGISTER
	SYSCTL->RCC &= ~(1u<<20); // 16MHz
	
// -------- SETTING PF2 FOR PWM1 CHANNEL6 OUTPUT PIN ---------
	// SET PF2 A ALTERNATE FUNCTION : GPIOAFSEL REGISTER
	GPIOF->AFSEL |= (1<<2);
	
	// MAKE PF2 PWM OUPUT PIN : GPIOPCTL REGISTER
	GPIOF->PCTL = 0x0000500;
	
	// SET PF2 DIGITAL PIN
	GPIOF->DEN |= (1<<2);

// -------- PWM1 CHANNEL 6 CONFIDURATION ---------
	// DISABLE GENERATOR 3 COUNTER : PWMnCTL REGISTER
	PWM1->_3_CTL &= ~(1U<<0);
	
	// SELECT DOWN COUNT MODE OF COUNTER 3
	PWM1->_3_CTL &= ~(1U<<1);
	
	// SET LOAD VALUE FOR 10 KHz = 16MHz/1600 
	// 1 / 10 KHz = 0.1ms = TON + TOFF
	// LOAD VALUE = CLOCK FREQUENCY / DESIRED FREQUENCY
	PWM1->_3_LOAD = 1600;
	
	/* 
		1KHz
		PWM1->_3_LOAD = 16000;
		WM1->_3_CMPA = 8000;
	*/
	
	// SET DUTY CYCLE TO 50% OF 1600 : PWM1CMPA REGISTER
	PWM1->_3_CMPA = 800;
	
	// SET PWM OUTPUT WHEN COUNTER RELOADED AND CLEAR WHEN MATCHES PWMCPMA : PWMnGENA REGISTER
	PWM1->_3_GENA |= (1<<2) | (1<<3) | (1<<7);
	PWM1->_3_GENA &= ~(1U<<6);
	
	// ENABLE GENERATOR 3 COUNTER : PWMnCTL REGISTER
	PWM1->_3_CTL = 1;        
	
	// ENABLE PWM1 CHANNEL 6 OUTPUT : ENABLE REGISTER
	PWM1->ENABLE |= (1<<6);
	
	
	
	
	while(1)
	{
		for(i=0;i<1600;i++)
		{
			PWM1->_3_CMPA = i;
			delay(10000);
		}
		
		delay(1000000);
		
		for(i=1600;i>0;i--)
		{
			PWM1->_3_CMPA = i;
			delay(10000);
		}
	
		delay(1000000);
		
	}
	
	
}


void delay(long d)
{
	while(d--);
}
