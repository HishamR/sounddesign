/***************************************************************

	Skeleton project for signal processing labs
	
	Tommy Andersson 2013-12-10
	
	The signal processing code is to be placed in sampel_int.c

****************************************************************/


#include <asf.h>

#include "adcdac.h"
#include "conf_tc.h" 
#include "sampel_int.h"



int main (void)
{

	sysclk_init();
	board_init();
	ioport_init();

	ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);	
	adc_setup();
	dac_setup();
	configure_tc();
	
	while(1);			//Do nothing in main program
}

