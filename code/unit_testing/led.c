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

#ifndef UNIT_TEST


/***************************************************************************//**
 * @brief
 *   Ex_LED_Task
 *   This task takes care of readinf the flags that are passed to it periodically,
 *   then it goes through logic to make sure the LEDs are flashed at the proper pwm rate
 *   corresponding to the amount of force or if the game has ended.
 *
 *
 * @param  p_arg
 *  pointer to unused passed arguments
 *

 ******************************************************************************/
void  EX_LED_Task (void  *p_arg){
	RTOS_ERR  err;
	uint8_t flags = 0;
	uint8_t led_drive;
	uint16_t count = 0;

	//initialize the LED gpios
	BSP_LedsInit();
	BSP_LedClear(0);
	BSP_LedClear(1);

	while(1){
		flags = led_nonblocking_flags; //read flags from non blocking atomic flag data
		led_nonblocking_flags = 0;// remove the flags
		led_drive = pwm_LED_driver(force_percentage, flags);

		if(led_drive & LED0){
			BSP_LedSet(0);
		}
		else{
			BSP_LedClear(0);
		}

		//periodic flashing at 1 Hz
		if(led_drive & LED1){
			count = (count+1)%200;
			if(count == 0){
				BSP_LedToggle(1);
			}
		}

		OSTimeDly(1, OS_OPT_TIME_DLY, &err); //needs to be periodic for pwm
	}
}
#endif
