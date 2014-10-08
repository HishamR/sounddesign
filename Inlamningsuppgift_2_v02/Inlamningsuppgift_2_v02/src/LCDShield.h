/*
* LCDShield.h
*
* Created: 2013
*  Author: Ulrik
*
* Modified: 2014-10-08 17:09:00
*  Author: Hisham Ramish and Hamit Sen
*/


#ifndef LCDShield_h
#define LCDShield_h

#include "asf.h" /* Ugly but necessary */

#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define LCD_mask_D4_D7 0b00000111100000000000000000000000

void delay_init(void);
void delay(uint32_t);
int LCDInit(void);
uint8_t LCDwrite(uint8_t, bool);
void ADCsetup(void);
int LCDClear(void);
int LCDwriteInteger(int);
int LCDwriteString(const char* str);
int LCDputCursor(uint8_t row, uint8_t col);

#endif
