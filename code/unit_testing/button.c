/**
 *  @file   button.c
 *  @brief  This file holds the pushbutton task and all handling related to that
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "button.h"



/***************************************************************************//**
 * @brief
 *   button_decoder
 *   This function holds previous information about the other flags and tells if only one button
 *   is pressed at a time and if this is correct it outputs the correspnding increment or decrement
 *
 * @param  flags
 * 	Whatever flag caused the function to wake up
 *
 ******************************************************************************/

button_result button_decoder(uint8_t flags){
	return button_nothing;
}


void  Ex_PushbuttonTask (void  *p_arg){
}
