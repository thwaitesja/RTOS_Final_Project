/**
 *  @file   lcd.c
 *  @brief  This file holds the lcd task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "lcd.h"
#include "trig.h"

#ifndef UNIT_TEST
/***************************************************************************//**
 * @brief
 *   Draw_base
 *   Given the cart information this function draws the cart base on the screen
 *
 *   base looks like:
 *	 *********
 *   ***   ***
 *   * *   * *
 *   ***   ***
 *
 * @param gc - a pointer to the graphics of the board
 *
 * @param x - the location of the base of the cart
 ******************************************************************************/
static void Draw_base(GLIB_Context_t* gc, int x){
	for(int i = x-4; i<x+5; i++){
		if(i>0 && i <128){//checks to make sure it is in the screen
			GLIB_drawPixel(gc, i, 124);
			if((i < x-1)||(i>x+1)){//draw the wheels
				GLIB_drawPixel(gc, i, 125);
				GLIB_drawPixel(gc, i, 127);
				if((i != x-3)&&(i!=x+3)){
					GLIB_drawPixel(gc, i, 126);
				}
			}
		}
	}
}

/***************************************************************************//**
 * @brief
 *   Draw_ball
 *   Given the cart information this function draws a ball on the screen for the weight of the pendulum
 *
 *   ball looks like:
 *	 ***
 *	 * *
 *	 ***
 *
 * @param gc - a pointer to the graphics of the board
 *
 * @param x - the location of the ball in x
 *
 * @param y - the location f the ball in y
 ******************************************************************************/
static void Draw_ball(GLIB_Context_t* gc, int x, int y){
	for(int i = x-1; i<x+2; i++){
		for(int j = y-1; j<y+2; j++){
			if((x-i)||(y-j)){//doesn't draw on the given pixel
				GLIB_drawPixel(gc, i, j);
			}
		}
	}
}

/***************************************************************************//**
 * @brief
 *   Draw_cart
 *   Given the cart information this task draws the cart on the screen
 *
 * @param gc - a pointer to the graphics of the board
 *
 * @param Display_info - a struct containing the info to draw the display
 ******************************************************************************/
static void Draw_cart(GLIB_Context_t* gc, struct Display_Info Display_info){

	//get absolute offsets
	int range = config.xmax - config.xmin;//move min to 0 relative-  get the whole range
	int base = (Display_info.base_pos - config.xmin)/ (range>>7); // where base is now where the base of the pendulum from 0 to 128
	Draw_base(gc, base);

	int angle = Display_info.angle;

	int x_start = base;
	int y_start = 123;

	int x_stop = base + (sin_int(angle)>>4);
	int y_stop = 123-(cos_int(angle)>>4);

	GLIB_drawLine(gc, x_start, y_start, x_stop, y_stop);
	Draw_ball(gc, x_stop, y_stop-1);

}


static GLIB_Context_t gc = {0};

/***************************************************************************//**
 * @brief
 *   Display setup
 *   sets up the display before the os is configured to prevent timer malfunctions
 ******************************************************************************/
void Display_setup(){
	EMSTATUS status;



	 /* Initialize display module */
	  status = DISPLAY_Init();
	  if (DISPLAY_EMSTATUS_OK != status) {
		while(1);
	  }
	  /* Initialize the DMD module for the DISPLAY device driver. */
	  status = DMD_init(0);
	  if (DMD_OK != status) {
		while(1);
	  }
	  /*init the GLIB*/
	  status = GLIB_contextInit(&gc);
	  if (GLIB_OK != status) {
		  while(1);
	  }

	  GLIB_setFont(&gc, (GLIB_Font_t *)&GLIB_FontNarrow6x8);
	  gc.backgroundColor = White;
	  gc.foregroundColor = Black;
}

/***************************************************************************//**
 * @brief
 *   LCD_DisplayTask
 *   Operating system task for initializing the Display, then updating the display
 *   every time that the task receives an update from the physics task.
 *
 * @param p_arg - a unused pointer to any arguments passed
 ******************************************************************************/
void  EX_Display_Task (void  *p_arg){
	RTOS_ERR  err;
	OS_MSG_SIZE msg_sz;
	struct Display_Info* D_info = 0;


//
	  while(1){
			//update LCD output
			D_info = *(struct Display_Info**)OSQPend (&message_Q, 0, OS_OPT_PEND_BLOCKING, &msg_sz,0,&err);
			GLIB_clear(&gc);

			Draw_cart(&gc, *D_info);
			  /* Update display */
			DMD_updateDisplay();
			free(D_info);
	  }

}
#endif
