/*
 * sample_int.h
 *
 * Created: 2013-12-10 08:30:13
 *  Author: Tommy
 *
 * Modified: 2014-10-08 17:09:00
 *  Author: Hisham Ramish and Hamit Sen
 */


#ifndef SAMPEL_INT_H_
#define SAMPEL_INT_H_

#define CHECK_PIN PIO_PB26_IDX	//Ardiuno Due pin 22 used to measure work load

void LCDupdate(uint8_t pos, uint16_t val, const char *unit);
void TCO_Handler(void);


#endif /* SAMPEL_INT_H_ */