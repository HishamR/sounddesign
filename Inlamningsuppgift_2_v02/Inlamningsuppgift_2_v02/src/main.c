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
#include "sample_int.h"
#include "delay.h"

int main(void) {
	
	sysclk_init();
 	board_init();
 	ioport_init();
 	adc_setup();
 	dac_setup();
 	delay_init();
 	configure_tc();
	lcd_init();
	
	/*
	* Start the program
	*/
	lcd_clear();
	lcd_write_str(("DELAY  ECHO"));
	LCDupdate(0b11000000, ((4999 + 1) / 10), "ms");
	LCDupdate(0b11001010, 50, "%");
	
	while(1);
}

