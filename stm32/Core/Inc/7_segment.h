/*
 * 7_segment.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */

#ifndef INC_7_SEGMENT_H_
#define INC_7_SEGMENT_H_

#include "global.h"

#define MAX_LED	4

void display_7SEG(int num);
void update7SEG(int index);
void updateClockBuffer();
void scan7sSEG();
extern int led_index;

#endif /* INC_7_SEGMENT_H_ */
