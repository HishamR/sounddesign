/*
* main.c
*
* Created: 2014-10-08 21:09:29
*  Author: Hisham Ramish and Hamit Sen
*/

#include <asf.h>
#include "adc_dac.h"
#include "conf_tc.h"
#include "LCDShield.h"
#include "sampel_int.h"
#include "delay.h"

int main(void) {
	
	sysclk_init();
	board_init();
	ioport_init();
	adc_setup();
	dac_setup();
	DelayInit();
	LCDInit();
	
	/*
	* Start the program
	*/
	
	LCDwriteString(("DELAY  ECHO"));
	LCDupdate(0b11000000, ((4999 + 1) / 10), "ms");
	LCDupdate(0b11001010, 50, "%");
	configure_tc();
	
	while(1);
}

