#include "TM4C123.h"                    // Device header

/*
	ADC0 --> AIN0 --> PE3
*/

void delay(long d);

uint16_t adc_value;

int main(void)
{

	
	// CONFIGURATION GPIO AS ADC CHANNEL : ADC0 --> AIN0
	
	// 1. Enable the ADC clock using the RCGCADC register
	SYSCTL->RCGCADC |= (1<<0);
	
	// 2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register.
	// To find out which GPIO ports to enable, refer to Signal Description
	SYSCTL->RCGCGPIO |= (1<<4);
	
	// 3. Set the GPIO AFSEL bits for the ADC input pins To determine which GPIOs to configure
	GPIOE->AFSEL |= (1<<3);
	
	// 4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
	// GPIO Digital Enable (GPIODEN) register
	GPIOE->DEN &= ~(1U<<3);
	
	// 5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
	// the appropriate bits of the GPIOAMSEL register in the associated GPIO block
	GPIOE->AMSEL |= (1<<3);
	
	// 6. If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI
	// register. The default configuration has Sample Sequencer 0 with the highest priority and Sample
	// Sequencer 3 as the lowest priority.
	
	
	
	// CONFIGURATION OF SAMPLE SEQUENCER FOR ADC CHANNEL
	
	// 1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
	// ADCACTSS register. Programming of the sample sequencers is allowed without having them
	// enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
	// event were to occur during the configuration process.
	ADC0->ACTSS &= ~(1U<<3);
	
	// 2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
	ADC0->EMUX &= ~(0xF000U);
	
	// 3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
	// ADCTSSEL) register to specify in which PWM module the generator is located. The default
	// register reset selects PWM module 0 for all generators.
	
	
	// 4. For each sample in the sample sequence, configure the corresponding input source in the
	// ADCSSMUXn register.
	ADC0->SSMUX3 = 0x0;
	
	// 5. For each sample in the sample sequence, configure the sample control bits in the corresponding
	// nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
	// is set. Failure to set the END bit causes unpredictable behavior.
	ADC0->SSCTL3 |= (1<<1) | (1<<2);
	
	// 6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
	
	
	// 7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
	// register.
	ADC0->ACTSS |= (1<<3);
	
	SYSCTL->RCGCGPIO =  0x20;  // ENABLE CLOCK FOR PORTF	
	GPIOF->DEN = 0x0E; // PF1,PF2,PF3 AS DIGITAL OUTPUTS
	GPIOF->DIR = 0x0E; // PF1,PF2,PF3 AS OUTPUT
	
	while(1)
	{
		// START CONVERSION PROCESS
		ADC0->PSSI |= (1<<3);
		
		// POOLLING ON INTERRUPT FLAG CONVERSION FOR EACH SAMPLE
		while( (ADC0->RIS & (1<<3) >>3) == 0 ); // WAIT UNTILL CONVERSION COMPLETE
		adc_value = (uint16_t)ADC0->SSFIFO3; // READ CONVERSION VALUE
		ADC0->ISC |= (1<<3); // CLEAR INTERRUPT FLAG FOR STARTING ANOTHER CONVERSION
		
		if(adc_value > 2048)
		{
			GPIOF->DATA |= (1<<3);
		}
		else
		{
			GPIOF->DATA &= ~(1U<<3);
		}
		
	}
	
	
}

void delay(long d)
{
	while(d--);
}
