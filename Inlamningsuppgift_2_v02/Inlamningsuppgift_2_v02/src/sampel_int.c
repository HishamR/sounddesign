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
#include "sampel_int.h"
#include "LCDShield.h"
#include "adc_dac.h"

/************************************************************************/
/*	Updating information on the LCD                                     */
/************************************************************************/
void LCDupdate(uint8_t pos, uint16_t val, const char *unit) {
	
	char update[7];
	LCDwrite(pos, LOW);	//Cursor positioning
	delay(40);
	sprintf(update, "%d%s ", val, unit);	//Format
	LCDwriteString(update); //To display
}

/************************************************************************/
/*	Interrupt handler for TC0 interrupt.                                */
/************************************************************************/
void TC0_Handler(void) {
	
	static uint16_t i = 0;
	static uint16_t buffer[5000] = {0};
	uint32_t invalue, outvalue;
	
	tc_get_status(TC0, 0);
	adc_start(ADC);
	
	while ((adc_get_status(ADC) & 0x01000000) == 0);
	invalue = adc_get_channel_value(ADC, ADC_CHANNEL_10);	// Channel 10 used for Sampling
	adc_start(ADC);
	
	/*
	* Delay function
	*/
	buffer[i] = ((buffer[i] + invalue) * 50) / 100;
	i++;
	if (i >= 4999) {
		i = 0;
		
	outvalue = invalue + buffer[i];
	dacc_write_conversion_data(DACC, outvalue);
	
	/*
	* Button function
	*/
	invalue = adc_get_channel_value(ADC, ADC_CHANNEL_11);	//Channel 11 used for buttons
	
}
