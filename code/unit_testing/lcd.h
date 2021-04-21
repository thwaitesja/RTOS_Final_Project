/**
 *  @file   lcd.h
 *  @brief  This file contains all lcd defines
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/

#ifndef SRC_LCD_H_
#define SRC_LCD_H_

#ifndef UNIT_TEST
	#include  <kernel/include/os.h>
	#include "glib.h"
	#include "display.h"

	extern OS_Q message_Q;
#endif

#include "params.h"

void Display_setup();

void  EX_Display_Task (void  *p_arg);

struct Display_Info{
	int base_pos;
	int angle; //this angle is in radians*128
};



#endif /* SRC_LCD_H_ */
