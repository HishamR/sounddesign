/*
* myADC.c
*
* Created: 2013-11-25 16:16:35
*  Author: staff
*  Updated by Hisham Ramish, Hamit Sen 2014-01-09
*/

#include "asf.h"
#include <stdio.h>
#include "myADC.h"

int ADCSetup(int DuePinNr)


/*
*	Sets all available A/D channels to an array
*/
{
	int ADC_Channels[] = {ADC_CHANNEL_7,ADC_CHANNEL_6,ADC_CHANNEL_5,ADC_CHANNEL_4,
		ADC_CHANNEL_3,ADC_CHANNEL_2,ADC_CHANNEL_1,ADC_CHANNEL_0,ADC_CHANNEL_10,
	ADC_CHANNEL_11,ADC_CHANNEL_12,ADC_CHANNEL_13};


	/* Enable the specified peripheral clock (ADC clock) */
	if (pmc_enable_periph_clk(ID_ADC) == 0) {
		adc_init(ADC, sysclk_get_main_hz(), 14000000, 8 );
		adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
		adc_enable_channel(ADC, ADC_Channels[DuePinNr]);
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
		return 1;
	}
	return 0;
}
