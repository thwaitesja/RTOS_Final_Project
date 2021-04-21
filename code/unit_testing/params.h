/**
 *  @file   params.h
 *  @brief  This file contains all application control functionality
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

#include <stdint.h>

//There will be increments 0 through 8 for percentage 0 being 0% and 8 being 100%

void params_init();

typedef enum Variant{
	INVERTED_PENDULUM,
	INVERTED_PENDULUM_W_KICKER,
	POGO_STICK,
	POGO_STICK_W_FLYWHEEL
}Variant;


//this holds all the data of the data structure

#define VERSION 				2
#define GRAVITY 				980  				// 		mm/s^2
#define MASS_OF_POST 			100 				//   	g
#define LENGTH_OF_POST 			1000 				//		mm
//graphing limits
#define XMIN 					-3000				//		mm
#define XMAX 					3000				//		mm
#define VARIANT_SELECTED		INVERTED_PENDULUM	//		Inverted Pendulum
#define MAX_FORCE				1000				//		mN
#define MAX_IMPULSE				-1					//		g*m/s - not used in variant 1
#define NON_POLE_MASS			-1					//		g - not used in variant 1
#define POLE_COM				-1					//		mm - not used in variant 1
#define MAX_DISTANCE_FROM_POLE 	-1					//		mm - not used in variant 1 amount of distance additional mass can move
#define MAX_ANGULAR_MOMENTUM	-1					//		g*mm^2/s - not used in variant 1
#define NUMBER_OF_OBSTACLES		0

struct Obstacle{
	int xmin;	//mm
	int xmax;	//mm
	int height;	//mm
	struct Obstacle* next;
};


struct Params{
	uint8_t version;
	uint32_t gravity;
	uint32_t post_mass;
	uint32_t post_length;
	int xmax;
	int xmin;
	Variant v;
	uint32_t max_force;
	uint32_t max_impulse;
	uint32_t non_post_mass;
	uint32_t post_com;
	uint32_t max_dist_from_pole;
	uint32_t max_ang_mom;
	uint8_t obst_n;
	struct Obstacle* obst;
};

extern struct Params config;


#endif /* SRC_PARAMS_H_ */
