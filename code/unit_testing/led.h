/**
 *  @file   led.h
 *  @brief  This file contains all led defines
 *  @author Justin Thwaites
 *  @date   2020-4-6
 ***********************************************/

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include <stdint.h>
#include <stdbool.h>

#define LED0 1
#define LED1 2

void  EX_LED_Task (void  *p_arg);
uint8_t pwm_LED_driver(uint16_t percentage, uint8_t flags);




#endif /* SRC_LED_H_ */
