/*
* sample_int.c
*
* Created: 2013-12-10 08:30:13
*  Author: Tommy
*
* Modified: 2014-10-08 17:09:00
*  Author: Hisham Ramish and Hamit Sen
*/

#include <asf.h>
#include "sample_int.h"
#include "LCDShield.h"
#include "adc_dac.h"
#include "delay.h"

/************************************************************************/
/*	Interrupt handler for TC0 interrupt.                                */
/************************************************************************/
int lcd_update(uint16_t echo, uint16_t delay_btn){
	
	lcd_clear();
	lcd_cursor_pos(0,0);
	lcd_write_str(("ECHO: "));
	lcd_write_int(echo);
	lcd_write_str(("%"));
	
	lcd_cursor_pos(1,0);
	lcd_write_str(("DELAY: "));
	lcd_write_int(delay_btn/10);
	lcd_write_str(("ms"));
	return 1;
}

void TC0_Handler(void) {
	
	static uint16_t i = 0;
	static uint16_t buffer[5000] = {0};
	static uint16_t invalue, outvalue;
	static uint16_t echo = 50, delay_btn = 5000;
	
	tc_get_status(TC0, 0);
	adc_start(ADC);
	
	while ((adc_get_status(ADC) & 0x01000000) == 0);
	invalue = adc_get_channel_value(ADC, ADC_CHANNEL_10);	// Channel 10 used for Sampling
	adc_start(ADC);
	
	/*
	* Delay function
	*/
	buffer[i] = ((buffer[i] + invalue) * echo) / 100;
	i++;
	if (i >= delay_btn) {
		i = 0;
	}
	outvalue = invalue + buffer[i];
	dacc_write_conversion_data(DACC, outvalue);
	
	/*
	* Button function
	*/
	if ((i % 200) == 0) {
		invalue = adc_get_channel_value(ADC, ADC_CHANNEL_7);	//Channel 0 used for buttons
		if (invalue < 400) {	//Right button on the LCD Shield, set to increase the echo
			if (echo < 100) {	//Max value for the echo is 100
				echo ++;
				lcd_update(echo, delay_btn);
			}
		} else if ((invalue > 1500) & (invalue < 2000)) {	//Left button on the LCD Shield, set to decrease the echo
			if (echo > 0) {
				echo --;
				lcd_update(echo, delay_btn);
			}
		} else if ((invalue > 400) & (invalue < 1000)) {	//Up button on the LCD Shield, set to increase the delay
			if (delay_btn < 5000) {
				delay_btn += 10;
				if (delay_btn > 5000) {
					delay_btn = 5000;
				}lcd_update(echo, delay_btn);
			}
		} else if ((invalue > 1000) & (invalue < 1500)) {	//Down button on the LCD Shield, set to increase the echo
			if (delay_btn > 0) {
				delay_btn -= 10;
				if (delay_btn < 0) {
					delay_btn = 0;
				}lcd_update(echo, delay_btn);
			}
		}
	}
}
