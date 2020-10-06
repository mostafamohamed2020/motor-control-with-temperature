/* 
 * ADC .c
 * author : mostafa gomaa
 */

#include "ADC.h"

/*implementation of ADC_INIT */
void ADC_INIT(void)
{
	/* 
	 * description of ADMUX register
	 * using external voltage reference
	 * using right adjust 
	 */
	 ADMUX = 0;
	 
	 /* 
	  * description of ADCSR register
	  * enable ADC module
	  * disable ADC interrupt
	  * using FCPU/8 prescaller
	  */
	 ADCSRA |= ((1<<ADEN) | (1<<ADPS0) | (1<<ADPS1));
}

/*implementation of ADC_ReadChannel */
u_int16 ADC_ReadChannel(u_int8 channel)
{
	ADMUX &= 0xE0; /*clearing the first five bits*/
	ADMUX |= channel; /*storing the channel*/
	set_bit(ADCSRA , ADSC); /*set bit to start conversion*/
	while (bit_is_clear(ADCSRA , ADIF));
	{
		set_bit(ADCSRA , ADIF); /*clear the IF by write 1 to it*/
	}
	return ADC;
}