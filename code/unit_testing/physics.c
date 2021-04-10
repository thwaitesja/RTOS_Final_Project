/**
 *  @file   physics.c
 *  @brief  This file holds the physics task and all handling related to that task
 *  		.
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "physics.h"


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
 * 	the percentage of the max force determined by the buttons
 *
 * 	@param  max force
 * 	the determined max force on the base
 *
 ******************************************************************************/
int force_generator(slider_value direction, uint16_t force_percentage, uint32_t max_force){
	return 0;
}



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
 * 	the  irection of the applied force
 *
 * 	@param  time_step
 * 	how long the force is applied for
 *
 * @param  current state
 *  pointer to data holding what the current state is.
 *
 ******************************************************************************/
bool physics_engine(struct Params config, int force, uint32_t time_step, struct State *current_state){
	return true;
}


void  Ex_PhysicsTask (void  *p_arg){

}
