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
	slider_value slider_pos = slider_center;
	uint8_t low_val = 224;//threshold it must be below to not be considered the center

	if(!slider_vals[0]&&!slider_vals[1]&&!slider_vals[2]&&!slider_vals[3]){//all sliders are 0
		return slider_error;
	}
	for(int i=0; i<4; i++){
		if(slider_vals[i] > 256){//max normalized value
			return slider_error;
		}
		if(slider_vals[i] < low_val){
			low_val = slider_vals[i];
			switch(i){
			case 0:
				slider_pos = slider_farleft;
			break;
			case 1:
				slider_pos = slider_left;
			break;
			case 2:
				slider_pos = slider_right;
			break;
			case 3:
				slider_pos = slider_farright;
			break;
			}
		}
	}

	return slider_pos;
}


void  EX_CapsenseSlider_Task (void  *p_arg){

}
