//
//  testADC_Runner.c
//  Playing with Unity
//
//  Created by Ulrik on 2013-11-19.
//  Modified by Hamit Sen & Hisham Ramish on 2014-01-09.
//
//

#include <setjmp.h>
#include <stdio.h>
#include <stdio_serial.h>
#include "asf.h"
#include "conf_board.h"
#include "unity.h"
#include "myADC.h"
#include "Delay.h"
#include "myADC.h"
#include "LCDShield.h"
#include "testmyADC.h"


static void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {

		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
		
		
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

static void runTest(UnityTestFunction test)
{
	if (TEST_PROTECT())
	{
		setUp();
		test();
	}
	if (TEST_PROTECT() && !TEST_IS_IGNORED	)
	{
		tearDown();
	}
}
void resetTest()
{
	tearDown();
	setUp();
}

int main(void)
{
	/* Initialize the Arduino Due system */
	sysclk_init();
	board_init();
	/* initialize the I/O-port used for transmitting data to the LCD-shield */
	ioport_init();
	/* Initialize the timer used for delays */
	delay_init();
	LCDInit();
	
	configure_console();
	
	Unity.TestFile = "test/testmyADC.c";
	UnityBegin();
	
	// Runs tests
	RUN_TEST(test_ADConverterIsInitialisedCorrectly, 10);
	RUN_TEST(test_CheckIfValueIsNotZero, 20);
	
	UnityEnd();
	return 0;
}


