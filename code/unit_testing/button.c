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
static bool flag_error = false;
static uint8_t button_states = 0;
button_result button_decoder(uint8_t flags){
	button_result result = button_nothing;


	//see if things are pressed
	if(button_0p & flags){
		button_states |= 1;
	}
	if(button_1p & flags){
		button_states |= 2;

	}

	//check if error
	if(button_states == 3){
		flag_error = true;

	}

	//see if increment or decrement occurs
	if(button_0r & flags){
		button_states &= ~1;
		result = button_decrement;
	}
	if(button_1r & flags){
		button_states &= ~2;
		result = button_increment;
	}

	//if error no increment or decrement
	if(flag_error){
		result =  button_nothing;
	}



	//check if no longer an error
	if(button_states == 0){
		flag_error = false;

	}
	return result;

}


void  Ex_PushbuttonTask (void  *p_arg){
}
