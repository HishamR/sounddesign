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
/*	Updating information on the LCD                                     */
/************************************************************************/
void LCDupdate(uint8_t pos, uint16_t val, const char *unit) {
	
	char update[7];
	lcd_write(pos, LOW);	//Cursor positioning
	delay(40);
	sprintf(update, "%d%s ", val, unit);	//Format
	lcd_write_str(update); //To display
}

/************************************************************************/
/*	Interrupt handler for TC0 interrupt.                                */
/************************************************************************/
void TC0_Handler(void) {
	
	static uint16_t i = 0;
	static uint16_t buffer[5000] = {0};
	uint32_t invalue, outvalue;
	uint16_t echo = 50, delay = 4999, steps = 10;
	
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
	if (i >= delay) {
		i = 0;
	}
	outvalue = invalue + buffer[i];
	dacc_write_conversion_data(DACC, outvalue);
		
		/*
		* Button function
		*/
	if ((i % 200) == 0) {
		invalue = adc_get_channel_value(ADC, ADC_CHANNEL_7);	//Channel 11 used for buttons
		if (invalue < 50) {	//Right button on the LCD Shield, set to increase the echo
			if (echo < 100) {	//Max value for the echo is 100
				echo += 5;
// 				LCDupdate(0b11001010, echo, "%");	//Update display with the new value for the echo
			}
			} else if (invalue < 1900) {	//Left button on the LCD Shield, set to decrease the echo
			if (echo > 0) {
				echo -= 5;
// 				LCDupdate(0b11001010, echo, "%");	//Update display with the new value for the echo
			}
			} else if (invalue < 700) {	//Up button on the LCD Shield, set to increase the delay
			if (delay < 5000) {
				delay += steps;
				if (delay > 5000) {
					delay = 5000;
				}
// 				LCDupdate(0b11000000, ((delay + 1) / 10), "ms");	//Update display with the new value for the delay
			}
			} else if (invalue < 1500) {	//Down button on the LCD Shield, set to increase the echo
			if (delay > 0) {
				delay -= steps;
				if (delay < 0) {
					delay = 0;
				}
// 				LCDupdate(0b11000000, ((delay + 1) / 10), "ms");	//Update display with the new value for the delay
			}
		}
	}
}
