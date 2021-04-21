/*
 * trig.h
 *
 *  Created on: Apr 19, 2021
 *      Author: thwai
 */

#ifndef SRC_TRIG_H_
#define SRC_TRIG_H_


int cos_int(int theta); 	//theta is in radians <<7
int sin_int(int theta);		//theta is in radians <<7
int acos_int(int ratio);    //ratio is multiplied by 256  returns an angle <<7

//returns a value that is between 1024 and 0 ie 1<<10

#endif /* SRC_TRIG_H_ */
