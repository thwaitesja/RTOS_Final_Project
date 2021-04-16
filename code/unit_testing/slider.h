/**
 *  @file   slider.h
 *  @brief  This file contains all slider defines
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/

#ifndef SRC_SLIDER_H_
#define SRC_SLIDER_H_

#include <stdint.h>
#include "capsense.h"

typedef enum slider_value{
	slider_center,
	slider_farleft,
	slider_left,
	slider_right,
	slider_farright,
	slider_error = -1,
}slider_value;

void  EX_CapsenseSlider_Task (void  *p_arg);
slider_value capsense_getVal(uint32_t* slider_vals);

#endif /* SRC_SLIDER_H_ */
