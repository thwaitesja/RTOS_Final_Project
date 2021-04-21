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
#include "lcd.h"
#include "led.h"
#include <stdint.h>
#include <stdbool.h>

extern uint16_t force_percentage;
extern slider_value  force_direction_data;

struct State{
	int angle;  // defined as radians *128 or 1rad<<7
	int p_x;
	int p_y;
	int v_x;
	int v_y;
};

void  Ex_PhysicsTask (void  *p_arg);
int force_generator(slider_value direction, uint16_t force_percentage, uint32_t max_force);
bool physics_engine(struct Params config, int force, uint32_t time_step, struct State *current_state);

#endif /* SRC_PHYSICS_H_ */
