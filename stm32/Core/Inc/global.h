/*
 * global.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "main.h"
#include "7_segment.h"
#include "fsm_automatic.h"

#define INIT			0
#define RED1_YELLOW2	2
#define RED1_GREEN2		3
#define YELLOW1_RED2	4
#define	GREEN1_RED2		5

extern int status, red_duration, green_duration, yellow_duration;
extern int road1_counter, road2_counter;
extern int scan_duration;

#endif /* INC_GLOBAL_H_ */
