/**
 *  @file   led.c
 *  @brief  This file holds the LED task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "led.h"


/***************************************************************************//**
 * @brief
 *   pwm LED driver
 *   This function takes in atomic force percentage and the flags passed from other tasks and
 *   determines which LEDs should be on, as well as storing an internal counter to increment
 *   to generate pwm if called multiple times.
 *
 * @param  slider_vals
 * 	4 length array with all of the slider values normalized
 *
 ******************************************************************************/
uint8_t pwm_LED_driver(uint16_t percentage, uint8_t flags){
	return LED0;
}



void  EX_LED_Task (void  *p_arg){

}
