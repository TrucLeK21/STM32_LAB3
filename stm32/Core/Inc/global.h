/*
 * global.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "main.h"
#include "7_segment.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"

#define INIT			0
#define RED1_YELLOW2	1
#define RED1_GREEN2		2
#define YELLOW1_RED2	3
#define	GREEN1_RED2		4

#define	MAN_INIT		10
#define MAN_RED			11
#define MAN_YELLOW		12
#define MAN_GREEN		13

extern int status, red_duration, green_duration, yellow_duration;
extern int road1_counter, road2_counter;
extern int scan_duration;

#endif /* INC_GLOBAL_H_ */
