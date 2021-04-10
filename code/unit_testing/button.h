/**
 *  @file   button.h
 *  @brief  This file contains all button defines
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/





#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include <stdint.h>

typedef enum button_result{
	button_increment,
	button_decrement,
	button_nothing,
}button_result;

typedef enum button_flags{
	button_0p = 1,
	button_0r = 2,
	button_1p = 4,
	button_1r = 8,
}button_flags;


void  Ex_PushbuttonTask (void  *p_arg);
button_result button_decoder(uint8_t flags);

#endif /* SRC_BUTTON_H_ */
