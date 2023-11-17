/*
 * software_timer.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag, timer2_flag, timer3_flag;
extern int TICK;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
