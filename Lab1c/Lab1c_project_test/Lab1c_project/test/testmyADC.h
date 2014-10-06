/*
* TestADC.h
*
* Created: 2013-11-19
* Author: Ulrik
* Modified by Hamit Sen & Hisham Ramish on 2014-01-09.
*/

#include "asf.h"

#ifndef TESTADC_H_
#define TESTADC_H_



void setUp(void);
void tearDown(void);
void resetTest(void);
void test_ADConverterIsInitialisedCorrectly(void);
void test_CheckIfValueIsNotZero(void);


#endif /* TESTADC_H_ */