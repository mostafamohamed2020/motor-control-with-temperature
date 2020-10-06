/*
 * temperature_motor_controlling.c
 *
 * Created: 10/6/2020 4:49:20 PM
 *  Author: mostafa gomaa
 */
 
#include <avr/io.h>
//#define F_CPU 1000000UL  //microcontroller frequency
#include "my_lcd.h"   //including lcd drivers
#include "common_macros.h"  
#include "standard_types.h"
#include "ADC.h"  //including ADC drivers

void TMR0_PWM(u_int8 speed){
	/* 
	 * PWM mode
	 * FCPU/8 prescaller
	 * non-inverting mode
	 */
	TCNT0 = 0; //initial value
	TCCR0 |= ((1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01));
	OCR0 = speed;  //input value
}	

int main(void)
{
	unsigned long temp;  //variable to hold the temperature 
	DDRB |= (1<<PB0); //motor pins (IN1 IN2 EN1)
	DDRB |= (1<<PB1);
	DDRB |= (1<<PB3);
    DDRB |= (1<<PB4); //red led
	PORTB &= (~(1<<PB4)); //led is off
	PORTB &= (~(1<<PB0));  //motor is off in the beginning
	PORTB &= (~(1<<PB1));
	lcd_init();
	ADC_INIT();
	lcd_clear_screen();
	lcd_displaystring("Temp = ");
	lcd_displaycharacterat(1,10,'C');
	lcd_display_strindinlocation(2,0,"speed :");
	lcd_sendcommand(cursor_on);
	
    while(1)
    {
		lcd_gotorowcolumn(2,2);
		temp = ADC_ReadChannel(0);  //reading the analog value 
		temp =  temp = (temp*150*5)/(1023*1.5);
		lcd_gotorowcolumn(1,7);
		lcd_inttostr(temp); //display the temperature 
		
		if (temp >=0 && temp <25) //first mode
		{
			PORTB |= (1<<PB0);
			PORTB &= (~(1<<PB1));
			TMR0_PWM(90); //40% duty cycle
			lcd_display_strindinlocation(2,8,"LOW   ");
		}
		
	   else if (temp >=25 && temp < 35) //second mode
		{
			PORTB |= (1<<PB0);
			PORTB &= (~(1<<PB1));
			TMR0_PWM(126); //half duty cycle
			lcd_display_strindinlocation(2,8,"MIDUIM");
			
		}
		
		else if (temp >=35 && temp <= 55) //third mode
		{
			PORTB |= (1<<PB0);
			PORTB &= (~(1<<PB1));
			TMR0_PWM(255); //full duty cycle
			lcd_display_strindinlocation(2,8,"HIGH     ");
		}
		
		else  //lastmode
		{
			PORTB |= (1<<PB0); //stop the motor
			PORTB |= (1<<PB1);
			lcd_display_strindinlocation(2,8,"MOTOR oFF   ");
			/*led indication*/
		    PORTB |= (1<<PB4);
		    _delay_ms(1000);
		    PORTB &= (~(1<<PB4));
			_delay_ms(1000);
		}
    }
}