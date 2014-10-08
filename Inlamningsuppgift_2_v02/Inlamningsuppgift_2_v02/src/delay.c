/*
 * delay.c
 *
 * Created: 2014-10-08 17:09:00
 *  Author: Hisham Ramish and Hamit Sen
 */

#include "delay.h"

void DelayInit(void)
{
	pmc_enable_periph_clk(ID_TC3);
	tc_init(TC1,0,0);	/*TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC1,0);
	tc_stop(TC1,0);		/* Making sure the timer is not running */
}

void Delay(uint32_t us)
/* A Delay of us microseconds */
{
	tc_start(TC1,0);
	while (tc_read_cv(TC1,0) < us*42);	/* TIMER_CLOCK1 runs on MCK/2 */
	tc_stop(TC1,0);
}



