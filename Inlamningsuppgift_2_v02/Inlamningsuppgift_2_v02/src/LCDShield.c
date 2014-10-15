/*
* LCDShield.c
*
* Created: 2013
*  Author: Ulrik
*
* Modified: 2014-10-08 17:09:00
*  Author: Hisham Ramish and Hamit Sen
*/

#include "LCDShield.h"

int lcd_init(void)		/* Initializes the display on the LCD shield, returns 1 if everything is ok */
{
	int all_ok=0;		/* at the beginning assume nothing works */
	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(4100);	/* wait for more than 4,1 ms */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);

	delay(100);	/* wait 100 us */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);	/* wait 100 us */
	
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);

	lcd_write(0b00101000, LOW);		/* Two rows, small font */
	lcd_write(0b00001000, LOW);		/* Display off */
	lcd_write(0b00000001, LOW);		/* Display clear */
	
	delay(3000);
	
	lcd_write(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	lcd_write(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */

	all_ok = 1;					/* simple return statement showing that the initialization of the LCD has completed */
	return all_ok;
}


uint8_t lcd_write(uint8_t byte, bool type)		/* writes a byte to the LCD display */
/*
*	writes the byte (8 bits) to the LCD display as two consecutive 4 bits
*	type = 0 controls the display
*	type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
*
*	LCDwrite returns the actual pinout value on PIOC 26-23, which is the reverse order compared to the Due pin order of D4-D7
*/
{
	/* In it's infinite wisdom the shield has the data pins in mirrored order compared to the Due board */
	uint8_t mirror_pin[16]={0b0000,0b1000,0b0100,0b1100,0b0010,0b1010,0b0110,0b1110,0b0001,0b1001,0b0101,0b1101,0b0011,0b1011,0b0111,0b1111};
	uint32_t byte32;
	uint8_t byte_orig;
	uint8_t mirrored_output = 0;

	byte_orig = byte;

	/* write the first 4 bits to the shield. */
	byte = byte>>4;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte << 23;
	mirrored_output = byte<<4;
	
	ioport_set_pin_level(LCD_RS, type);
	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);
	
	/* write the second 4 bits to the shield. */
	byte = byte_orig;
	byte = byte & 0x0f;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte<<23;
	mirrored_output = mirrored_output + byte;

	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay(100);
	
	return mirrored_output;
}

int lcd_clear(void)
{
	int all_Ok = 0;
	lcd_write(0b00000001, LOW);
	delay(1600);
	all_Ok = 1;
	return all_Ok;
}

int lcd_write_int(int number)
{
	char output[10];
	sprintf(output, "%d", number);
	lcd_write_str(output);
	return 1;

}

/*
* Displays strings on the Arduino Shield Display
*/
int lcd_write_str(const char* str)
{
	int all_ok = 0;
	
	/*
	* Loops until break
	*/
	while (*str != '\0')
	{
		lcd_write(*str, HIGH);
		str++;
	}
	
	all_ok = 1;
	return all_ok;
}

int lcd_cursor_pos(uint8_t row, uint8_t col)
{
	lcd_write((128 | (row << 6) | col), LOW);
	delay(40);	//delay of 40ms
	return 1;
}