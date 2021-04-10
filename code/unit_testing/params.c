/**
 *  @file   params.c
 *  @brief  This file sets up all configurations
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/
#include "params.h"

struct Params config = {0};


/***************************************************************************//**
 * @brief
 *  params init function
 *   This function sets up the global struct with all the configurations of the project designed in params.h
 *
 * @note
 * 	 This just puts defines in a struct
 ******************************************************************************/
void params_init(){
	//initializes the param struct
	config.version = VERSION;
	config.gravity = GRAVITY;
	config.post_mass = MASS_OF_POST;
	config.post_length = LENGTH_OF_POST;
	config.xmin = XMIN;
	config.xmax = XMAX;
	config.v = VARIANT_SELECTED;
	config.max_force = MAX_FORCE;
	config.non_post_mass = NON_POLE_MASS;
	config.post_com = POLE_COM;
	config.max_dist_from_pole = MAX_DISTANCE_FROM_POLE;
	config.max_ang_mom = MAX_ANGULAR_MOMENTUM;
	config.obst_n = NUMBER_OF_OBSTACLES;
	config.obst = 0;
}
