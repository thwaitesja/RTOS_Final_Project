/**
 *  @file   slider.c
 *  @brief  This file holds the capsense slider task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "slider.h"

/***************************************************************************//**
 * @brief
 *   capsense_getVal
 *   This function takes in the slider values from an array and then returns which direction the slider is pointing
 *
 * @param  slider_vals
 * 	4 length array with all of the slider values normalized
 *
 ******************************************************************************/
slider_value capsense_getVal(uint32_t* slider_vals){
	return slider_center;
}


void  EX_CapsenseSlider_Task (void  *p_arg){

}
