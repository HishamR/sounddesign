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

#include <stdio.h>
#include <string.h>
#include "asf.h"
#include "delay.h"

#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define LCD_mask_D4_D7 0b00000111100000000000000000000000

int lcd_init(void);
uint8_t lcd_write(uint8_t, bool);
int lcd_clear(void);
int lcd_write_int(int);
int lcd_write_str(const char* str);
int lcd_cursor_pos(uint8_t row, uint8_t col);

#endif
