/**
 *  @file   slider.c
 *  @brief  This file holds the capsense slider task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "slider.h"

#ifndef UNIT_TEST
/**********************Static************************************************/
static OS_TMR   cap_timer;
static uint8_t current_channel = 0;

/***************************************************************************//**
 * @brief
 *   A wrapper function to handle using capsense to measure as a callback,
 *   This also posts the semaphore when done measuring to allow the meausrement of the capsense
 *
 * @param p_tmr - a unused pointer to any arguments passed
 *
 * @param p_arg - a unused pointer to any arguments passed
 ******************************************************************************/

void Capsense_callback(void *p_tmr, void *p_arg){
	PP_UNUSED_PARAM(p_tmr);
	PP_UNUSED_PARAM(p_arg);


	Capsense_record_channel(current_channel);//measure previous channel
	current_channel = (current_channel+1)%NUM_SLIDER_CHANNELS;
	Capsense_start_record_channel(current_channel);//start new channel measurement

	RTOS_ERR  err;
	if(current_channel==0){//everytime all the channels have been updated, release the data to change the force direction
		OSSemPost(&slider_semaphore, OS_OPT_POST_1, &err);
	}
}


/***************************************************************************//**
 * @brief
 *   Ex_CapsenseSlider_Task
 *   This task takes care of areading the slider when it has been measured, then updates the shared data and goes back to sleep.
 *
 *
 * @param  p_arg
 *  pointer to unused passed arguments
 *

 ******************************************************************************/

void  EX_CapsenseSlider_Task (void  *p_arg){
	RTOS_ERR  err;
	CAPSENSE_Init();
	uint32_t slider_vals[4];


	//	//create the timer to constantly measure the capsense so all that needs to happen is a periodic reading in Vehicle Monitor Task
	OSTmrCreate(&cap_timer,"Capsense Timer", 1, 3, OS_OPT_TMR_PERIODIC, (OS_TMR_CALLBACK_PTR)Capsense_callback, 0, &err);//This will call capsense sense every 100ms
	OSTmrStart (&cap_timer,&err);
	while(1){
		OSSemPend(&slider_semaphore, 0,	OS_OPT_PEND_BLOCKING, 0, &err);//wait for the measurement
		for(int i =0; i<4; i++){
			slider_vals[i] = CAPSENSE_getNormalizedVal(i);
		}
		force_direction_data = capsense_getVal(slider_vals);
	}
}
#endif

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
