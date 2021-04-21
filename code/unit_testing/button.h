/**
 *  @file   button.h
 *  @brief  This file contains all button defines
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/





#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <stdint.h>
#include <stdbool.h>

#ifndef UNIT_TEST
	#include <kernel/include/os.h>
	#include "em_gpio.h"
	#include "bsp.h"
	#include "em_cmu.h"

	extern OS_FLAG_GRP pushbutton_flags;
	extern uint16_t force_percentage;
#endif


#include "led.h"

typedef enum button_result{
	button_increment,
	button_decrement,
	button_nothing,
}button_result;

//typedef enum button_flags{
//	button_0p = 1,
//	button_0r = 2,
//	button_1p = 4,
//	button_1r = 8,
//};

#define button_0p 1
#define button_0r 2
#define button_1p 4
#define button_1r 8



void  Ex_PushbuttonTask (void  *p_arg);
button_result button_decoder(uint8_t flags);

#endif /* SRC_BUTTON_H_ */
