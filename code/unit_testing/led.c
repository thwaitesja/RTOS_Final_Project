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
 * @param  percentage
 * 	a value from 0 to 8 representing the percentage of the force applied
 *
 *
 * @param  flags
 * 	any flaggs passed to the task
 *
 ******************************************************************************/
static bool led1_on = false;
static uint8_t count = 0;
static uint8_t pcnt = 0;//default to min force percent

uint8_t pwm_LED_driver(uint16_t percentage, uint8_t flags){
	if(flags & LED1){//sets the latch to have LED 1 constantly on
		led1_on = true;
	}
	if(flags & LED0){//the force percentage has changed, read the new force percentage and reset the count
		pcnt = percentage;
		count = 0;
	}

	uint8_t led_status;

	//preset the led_status
	if(led1_on){
		led_status = LED1;
	}
	else{
		led_status = 0;
	}


	if(count < pcnt){
		led_status |= LED0;
	}

	count = (count+1)%8;//increment count for a pwm type function
	return led_status;
}



void  EX_LED_Task (void  *p_arg){

}
