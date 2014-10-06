/*
 * sampel_int.c
 *
 * Created: 2013-12-10 12:32:30
 *  Author: Tommy
 */ 

#include <asf.h>
#include "sampel_int.h"
#define M 9

//void TCO_Handler(void);

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;


	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	ioport_set_pin_level(CHECK_PIN,HIGH);		//put test pin HIGH 
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high

	invalue=adc_get_latest_value(ADC);			//get input value
	
	//************
	// Here should signal processing code be placed
	// outvalue=invalue;
	
//	static uint16_t buffer[10000]={0};
//	static uint32_t k=0;

//	buffer[k]=invalue;
//	k++;
//	if (k==10000) k=0;
//	outvalue = invalue + buffer[k];

	//***********
		static float xbuff[M+1]={0.0};

		static float b[M+1]={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};

		float sum=0;

		//outvalue = xbuff * b;

		for (int i = M-1; i >= 0; i--)

		{

			xbuff[i+1] = xbuff[i];

		}

		xbuff[0] =(float)invalue;

		for (int i = 0; i <= M; i++)

		{

			sum += xbuff[i] * b[i];

		}

		outvalue =(uint32_t)sum;

// static uint32_t xbuff[M+1]={0.0};
// static uint32_t b[M+1]={1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
// 
// uint32_t sum=0;
// 
// for (int i = M-1; i >= 0; i--)
// {
// 	xbuff[i+1] = xbuff[i];
// }
// xbuff[0] =invalue;
// 
// for (int i = 0; i <= M; i++)
// {
// 	sum += xbuff[i] * b[i];
// }
// 
// outvalue =sum/10000;


		
	dacc_write_conversion_data(DACC,outvalue);	//send output value to DAC
	
	ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
	
}
