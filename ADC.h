/* 
 * ADC .h
 * author : mostafa gomaa
 */

#define F_CPU100000000UL /*micro controller frequency*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "standard_types.h"
#include "common_macros.h"

/*function to initiate the ADC module*/
void ADC_INIT(void);
/*function to read value from channel*/
u_int16 ADC_ReadChannel(u_int8 channel);
