/**
 *  @file   physics.c
 *  @brief  This file holds the physics task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "physics.h"
#include "trig.h"
#include <math.h>

/***************************************************************************//**
 * @brief
 *   force generator
 *   This function takes in the atomic data from the two input tasks and the
 *   global max force and computes the force applied to the pendulum
 *
 * @param  direction
 * 	the direction of the pressed slider
 *
 *
 * @param  force percentage
 * 	the percentage of the max force determined by the buttons this is given as a number from 0-8 where 0 is 0% and 8 is 100%
 *
 * 	@param  max force
 * 	the determined max force on the base
 *
 ******************************************************************************/
int force_generator(slider_value direction, uint16_t force_percentage, uint32_t max_force){
	int force = (max_force*force_percentage)>>3; //max_f * f%/8
	switch(direction){
		case slider_center:
			return 0;
			break;
		case slider_farleft:
			return -1 * force;
			break;
		case slider_left:
			return -1*force>>1;
			break;
		case slider_right:
			return force>>1;
			break;
		case slider_farright:
			return force;
			break;
		default:
			while(1);
			break;
	}


}


#ifndef UNIT_TEST
/***************************************************************************//**
 * @brief
 *   physics engine
 *   This function takes in the current state of the pendulum data, the data configs the time step and the force
 *   and updates the current state
 *
 * @param  config
 * 	globally configured parameters
 *
 *
 * @param  force
 * 	the  direction of the applied force
 *
 * 	@param  time_step
 * 	how long the force is applied for
 *
 * @param  current state
 *  pointer to data holding what the current state is.
 *
 *
 *
 * @note   Fx = F(1-cos(2T))/2
 * 		   Fy = Fsin(2T)/2 + mg(d-1)
 ******************************************************************************/
bool physics_engine(struct Params config, int force, uint32_t time_step, struct State *current_state){
	/****************************************PRE CHECK************************************************/
	//exit if the angle is already on its side.
	if(current_state->angle == 201 || current_state->angle == -201){//this is pi/2*128
		return true;
	}
	//exit if the State is already past the edge
	if((current_state->p_x <= config.xmin<<10) || (current_state->p_x >= config.xmax<<10)){
		return true;
	}
	/****************************************Force Computation************************************************/
	int f_x = (force*(1024-cos_int(current_state->angle<<1)))>>1; //this is 1024 times what the force should be
	long int f_y;
	if(current_state->angle){
		//fy = mN*1024 + uN = therefore uN needs to be multiplied by 1.024 or add additonal 3*g*m/128
		f_y = config.gravity*config.post_mass/125*128;
		f_y*=-1;
		f_y += (force*sin_int(current_state->angle<<1)>>1);
	}
	else{//state is 0
		f_y = 0;
		current_state->v_y = 0; //pole cannot go up or down when theta = 0
	}
	/****************************************Acceleration Computation************************************************/
	int a_x = f_x/(int)config.post_mass;
	int a_y = f_y/(int)config.post_mass;//Units of 1024*m/s^2
	/****************************************Velocity Computation************************************************/
	current_state->v_x += a_x*time_step;
	current_state->v_y += a_y*time_step;//units of 1024*mm/s
	/****************************************Position Computation************************************************/
	current_state->p_x += ((current_state->v_x*(int)time_step)/1000);
	current_state->p_y += ((current_state->v_y*(int)time_step)/1000);//units of 1024*mm
	if(current_state->p_y < 0){
		current_state->p_y = 0;//would have hit the ground
	}
	/****************************************Angle Computation************************************************/
	//check to make sure height approx isn't above pole length
	if(current_state->p_y > (config.post_length <<10)){//put the angle to 0 if crossing over
		current_state->p_y = (config.post_length<<10); //approximation oversteps -> this means a cross over on angle
		current_state->angle = 0;
	}
	else if(current_state->angle==0){//if at 0 make the angle slightly off so it begins falling
		if(current_state->v_x > 0){
			current_state->angle = -1;//starts going negative
		}
		else if(current_state->v_x < 0){
			current_state->angle = 1;//starts going positive
		}
		else if(force > 0){
			current_state->angle = -1;//starts going negative
		}
		else if(force < 0){
			current_state->angle = 1;//starts going positive
		}

	}
	else if(current_state->angle>0){//compute angle if not crossing over and in positive region
		//current_state->angle = (int)(acos((float)(current_state->p_y / config.post_length)/1024 )*128);
		current_state->angle = acos_int((current_state->p_y/config.post_length)>>2);
	}
	else if(current_state->angle<0){//compute angle if not crossing over and in negative region
		//current_state->angle = (int)(-1*acos((float)(current_state->p_y / config.post_length)/1024 )*128);
		current_state->angle = -1*acos_int((current_state->p_y/config.post_length)>>2);
	}
	else{
		while(1);//error if goes here
	}


	/****************************************END Checks************************************************/

	//Check if the ball passed the min
	if(current_state->p_x <= config.xmin<<10) {
		current_state->p_x = config.xmin<<10;
		return true;
	}
	//Check if the ball passed the max
	if(current_state->p_x >= config.xmax<<10) {
		current_state->p_x = config.xmax<<10;
		return true;
	}

	//check if the angle horizontal
	if(current_state->angle >= 201){//this is in radians*128
		current_state->angle = 201;
		return true;
	}
	if(current_state->angle <= -201){//this is in radians*128
		current_state->angle = -201;
		return true;
	}
	return false;
}

/***************************************************************************//**
 * @brief
 *   Ex_PhysicsTask
 *   This task takes care of calculating the force based on the shared data, then it steps through
 *   calculating the increment of what the loation of the pendulum should be, sending this update to the LCD update task.
 *
 *
 * @param  p_arg
 *  pointer to unused passed arguments
 *

 ******************************************************************************/

void  Ex_PhysicsTask (void  *p_arg){
	RTOS_ERR  err;
	struct Display_Info* D_info = 0;
	int applied_force = 0;
	struct State current_state = {0};
	current_state.p_y = config.post_length<<10;

	uint32_t time_step = 50;

	while(1){
		OSTimeDly(time_step, OS_OPT_TIME_DLY, &err);
		applied_force = force_generator(force_direction_data, force_percentage, config.max_force);
		if(physics_engine(config, applied_force, time_step, &current_state)){
			led_nonblocking_flags |= LED1;
		}




		D_info = (struct Display_Info*) malloc(sizeof(struct Display_Info*));
		D_info->angle= current_state.angle;
		D_info->base_pos = config.post_length*sin_int(current_state.angle);
		D_info->base_pos = (current_state.p_x - D_info->base_pos)>>10;

		OSQPost(&message_Q, (void *)&D_info, 1, OS_OPT_POST_FIFO + OS_OPT_POST_ALL, &err);
	}

}
#endif
