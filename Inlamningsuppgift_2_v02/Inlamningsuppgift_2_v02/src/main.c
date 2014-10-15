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
	lcd_cursor_pos(0,0);
	lcd_write_str("VERSION 9000");
	delay(2000000);
	lcd_clear();
	lcd_update(50, 5000);
	
	/*
	* Start the program
	*/
	
	while(1);
}

