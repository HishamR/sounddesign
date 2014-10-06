/**
*
*  main.c
*
*  Created by Ulrik in the class in 2013.
*  Modified by Hamit Sen & Hisham Ramish on 2014-01-09.
*
*/

#include <setjmp.h>
#include <stdio.h>
#include "asf.h"
#include "myADC.h"
#include "LCDShield.h"

int main (void)
{
	
	/* Initialize the Arduino Due system */
	sysclk_init();
	board_init();
	/* initialize the I/O-port used for transmitting data to the LCD-shield */
	ioport_init();
	/* Initialize the timer used for delays */
	delay_init();
	LCDInit();
	


	/* Initialize the console UART used from within Atmel Studio*/
	
	if (ADCSetup(0) == 0) {
		LCDwriteString("ERROR");
		while (1);
	}
	else{
		LCDwriteString("OK");
	}
	
	uint32_t result;
	
	while(1)
	{
		
		adc_start(ADC);
		delay(500000);
		LCDClear();
		result = adc_get_latest_value(ADC);
		
		
		LCDwriteInteger(result);
		LCDwriteString("mV");
		LCDwriteString(" Btn: ");
		
		
		/* The values aren't exactly like calculated
		but given a buffert to avoid errors */
		
		if (result < 50 ){
			LCDwriteString("right");
		}
		else if (result < 700 ){
			LCDwriteString("up");
		}
		else if (result < 1500 ){
			LCDwriteString("down");
		}
		else if (result < 1900 ){
			LCDwriteString("left");
		}
		else if (result < 2500 ){
			LCDwriteString("select");
		}
		else {
			LCDwriteString("none");
		}
		
	}

}
