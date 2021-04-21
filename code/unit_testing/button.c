/**
 *  @file   button.c
 *  @brief  This file holds the pushbutton task and all handling related to that
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "button.h"


#ifndef UNIT_TEST
/***************************************************************************//**
 * @brief
 * Setup GPIO
 * This function sets up the GPIO pins for the Pearl Gecko Push Buttons
 * and if Interrupt mode is enabled turns on the interrupts for the Push Buttons
 ******************************************************************************/
static void gpioSetup(void)
{
  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure PB0 as input*/
  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInputPull, 1);

  /* Configure PB1 as input */
  GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeInputPull, 1);


  /*Configure Interrupts for PB0 and PB1 */
  GPIO_IntConfig(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, true, true, true);
  GPIO_IntConfig(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, true, true, true);

  /*Clear odd and even IRQs and enable them*/
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
}

/***************************************************************************//**
 * @brief GPIO Interrupt handler for PB0 interrupt
 * 		Clears the corresponding interrupt for BSP_GPIO_PB0
 *      Then it pushes to a fifo data structure by using the custom built accessor function
 *      push_FIFO
 *
 * @note  to provide additional error correcting, there is a flag for the on flag and for the
 * off flag
 *
 ******************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
	  /* Get and clear PB0 interrupts */
	  uint32_t interruptMask = GPIO_IntGet();
	  RTOS_ERR  err;
	  GPIO_IntClear(interruptMask);
	  bool PB0 = !(bool)GPIO_PinInGet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN);//pushbutton values are inverted

	  if(PB0){
		  OSFlagPost(&pushbutton_flags, button_0p, OS_OPT_POST_FLAG_SET,&err);
	  }
	  else{
		  OSFlagPost(&pushbutton_flags, button_0r, OS_OPT_POST_FLAG_SET,&err);
	  }

}

/***************************************************************************//**
 * @brief GPIO Interrupt handler for PB1 interrupt
 * 		Clears the corresponding interrupt for BSP_GPIO_PB1
 *      Then it pushes to a fifo data structure by using the custom built accessor function
 *      push_FIFO
 ******************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
	  /* Get and clear PB1 interrupts */
	  uint32_t interruptMask = GPIO_IntGet();
	  RTOS_ERR  err;
	  GPIO_IntClear(interruptMask);
	  bool PB1 = !(bool)GPIO_PinInGet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN);//pushbutton values are inverted

	  if(PB1){
		  OSFlagPost(&pushbutton_flags, button_1p, OS_OPT_POST_FLAG_SET,&err);
	  }
	  else{
		  OSFlagPost(&pushbutton_flags, button_1r, OS_OPT_POST_FLAG_SET,&err);
	  }
}


/***************************************************************************//**
 * @brief
 *   Ex_PushbuttonTask
 *   This task takes care of any pushbuttons and modifies the force data accordingly
 *
 *
 * @param  p_arg
 *  pointer to unused passed arguments
 *

 ******************************************************************************/
void  Ex_PushbuttonTask (void  *p_arg){
	RTOS_ERR  err;
	uint8_t flags = 0;
	button_result force_change = button_nothing;

	//initialize the pushbutton gpios
	gpioSetup();

	while(1){

		flags = OSFlagPend(&pushbutton_flags, button_0r|button_0p|button_1r|button_1p, 0, OS_OPT_PEND_FLAG_SET_ANY|OS_OPT_PEND_FLAG_CONSUME,0, &err);
		force_change =  button_decoder(flags);

		if((force_change == button_increment)&&(force_percentage <8)){
			force_percentage++;
			led_nonblocking_flags |= LED0;//add flag to non blocking flag group
		}
		if((force_change == button_decrement)&&(force_percentage >0)){
			force_percentage--;
			led_nonblocking_flags |= LED0;//add flag to non blocking flag group
		}
	}
}
#endif


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
