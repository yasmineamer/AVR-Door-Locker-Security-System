/*
 * ADC.c
 *
 *  Created on: Sep 23, 2020
 *   Author: Yasmine_Amer
 */

#include "ADC.h"

volatile uint16 g_adcResult = 0;

ISR (ADC_vect)
{
	g_adcResult = ADC ;
}


void ADC_init(const ADC_configType *config_ptr)
{
	/*Adjust Vref*/
	ADMUX =((config_ptr -> vref)<<6);
	/*enable ADC
	 * choose ADC Clock
	 * Enable or disable interrupt if conversion complete
	 */
	ADCSRA = (1<<ADEN) | ((config_ptr -> interrupt)<<ADIE) | (config_ptr ->clk);

}

void ADC_readChannel(uint8 channel_num)
{
	ADMUX =(ADMUX & 0xE0) | (channel_num & 0x07);
	SET_BIT(ADCSRA , ADSC);

	/* polling if interrupt Disabled */
	if(BIT_IS_CLEAR(ADCSRA ,ADIE))
	{

		while(BIT_IS_CLEAR(ADCSRA,ADIF));
		SET_BIT(ADCSRA ,ADIF);
		g_adcResult = ADC ;
	}

}


