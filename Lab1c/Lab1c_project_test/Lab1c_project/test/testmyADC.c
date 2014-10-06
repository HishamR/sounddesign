//
//  testmyADC.c
//  Playing with Unity
//
//	Created by Ulrik on 2013-11-19.
//  Modified by Hamit Sen & Hisham Ramish on 2014-01-09.
//
//

#include "unity.h"
#include "testmyADC.h"
#include "myADC.h"
#include "Delay.h"
#include "asf.h"

void setUp(void)
{
	
}

void tearDown(void)
{
	
}

void test_ADConverterIsInitialisedCorrectly(void)
{
	/* Define a pointer to the address of the ADC Channel Status Register */
	uint32_t *const p_ADC_CHSR = (uint32_t *) (0x400C0018U);
	
	TEST_ASSERT_EQUAL_INT32(1, ADCSetup(0));
	
	/* Insert test assertion(s) here, checking that the corresponding ADC channel is enabled */
	TEST_ASSERT_BIT_HIGH(7, *p_ADC_CHSR);
}

void test_CheckIfValueIsNotZero(void)
{
	
	adc_start(ADC);
	Delay(1000000);
	TEST_ASSERT_TRUE(adc_get_latest_value(ADC) != 0);
}
