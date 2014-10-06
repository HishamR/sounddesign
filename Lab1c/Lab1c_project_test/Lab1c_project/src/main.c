/**
* \file
*
* \brief Empty user application template
*
*/

/**
* \mainpage User Application template doxygen documentation
*
* \par Empty user application template
*
* Bare minimum empty user application template
*
* \par Content
*
* -# Include the ASF header files (through asf.h)
* -# Minimal main function that starts with a call to board_init()
* -# "Insert application code here" comment
*
*/

/*
* Include header files for all drivers that have been imported from
* Atmel Software Framework (ASF).
*/

#include <setjmp.h>
#include <stdio.h>
#include "asf.h"
//#include "Delay.h"
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
	
	//	configure_console();
	
	        if (ADCSetup(0) == 0) {
		        LCDwriteChar("ERROR");
		        while (1);
	        }
	        else{
		        LCDwriteChar("OK");
	        }
	
	uint32_t result;
	
	while(1)
	{
		
		adc_start(ADC);
		delay(500000);
		LCDClear();		
		result = adc_get_latest_value(ADC);
		
		
		LCDwrite4(result);
		LCDwriteChar("mV");
		LCDwriteChar(" Btn: ");
		
		
		/* The values aren't exactly like calculated
		but given a buffert to avoid errors */
			
				if (result < 50 ){
					LCDwriteChar("right");
				}
				else if (result < 700 ){
					 LCDwriteChar("up");
				}
				else if (result < 1500 ){
					LCDwriteChar("down");
				}
				else if (result < 1900 ){
					 LCDwriteChar("left");
				}
				else if (result < 2500 ){
					 LCDwriteChar("select");
				} 
				else {
					LCDwriteChar("none");
				}
		
	}

	//Unity.TestFile = "test/testmyADC.c";
	//UnityBegin();
	
	// RUN_TEST calls runTest
	//RUN_TEST(test_ADConverterIsInitialisedCorrectly, 10);
	
	//UnityEnd();
	//return 0;
}
