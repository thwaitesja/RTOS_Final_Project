/**
 *  @file   physics.h
 *  @brief  This file contains all physics
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/

#ifndef SRC_PHYSICS_H_
#define SRC_PHYSICS_H_

#include "button.h"
#include "slider.h"
#include "params.h"
#include <stdint.h>
#include <stdbool.h>


struct State{
	int angle;
	int base_x_loc;
	int base_speed;
	int base_w_speed;
};

void  Ex_PhysicsTask (void  *p_arg);
int force_generator(slider_value direction, uint16_t force_percentage, uint32_t max_force);
bool physics_engine(struct Params config, int force, uint32_t time_step, struct State *current_state);

#endif /* SRC_PHYSICS_H_ */
