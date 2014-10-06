//
//  Delay.c
//
//	Modified by Hamit Sen & Hisham Ramish on 2014-01-09.
//

#include "Delay.h"

void DelayInit(void)
{
	pmc_enable_periph_clk(ID_TC0);
	tc_init(TC0,0,0);	/*TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC0,0);
	tc_stop(TC0,0);		/* Making sure the timer is not running */
}

void Delay(uint32_t us)
/* A Delay of us microseconds */
{
	tc_start(TC0,0);
	while (tc_read_cv(TC0,0) < us*42);	/* TIMER_CLOCK1 runs on MCK/2 */
	tc_stop(TC0,0);
}



