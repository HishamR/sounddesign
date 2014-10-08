/*
 * adc_dac.c
 *
 * The main purpose of this file is A/D and D/A conversion. Base of file is authored
 * by Tommy and later modified by Hisham and Hamit.
 *
 * Created: 2013-12-10 08:30:13
 *  Author: Tommy
 *
 * Modified: 2014-10-08 17:09:00
 *  Author: Hisham Ramish and Hamit Sen
 */ 

#include <asf.h>
#include "adc_dac.h"

void adc_setup() {
	
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);	//Configure for maximum frequency @ 84 MHz, CHECK THIS!!
	adc_configure_timing(ADC, 0, 0, 0);					//
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);		//
	adc_enable_channel(ADC, ADC_CHANNEL_10);			//Analog Input 8 on Arduino Due
	adc_enable_channel(ADC, ADC_CHANNEL_11);				//Analog Input 9 on Arduino Due
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);			//Trigger by Software
}

void dac_setup() {
	
	pmc_enable_periph_clk(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0);
	dacc_set_timing(DACC,1,1,0);						//1 is shortest refresh period, 1 max. speed, 0 startup time
	dacc_set_channel_selection(DACC,0);					//Channel DAC0
	dacc_enable_channel(DACC, 0);						//enable DAC0
}

