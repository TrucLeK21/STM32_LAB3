/*
 * button.h
 *
 *  Created on: Nov 12, 2023
 *      Author: Truc Le
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

// number of buttons
#define NUM_OF_BUTTON		3

// define duration when one of the buttons is hold
#define DURATION_FOR_AUTO_INCREASING	200

// define states for the buttons
#define PRESSED_STATE		GPIO_PIN_RESET
#define NORMAL_STATE		GPIO_PIN_SET

void button_reading();
int isbuttonPressed(int index);
void resetAllFlag();

#endif /* INC_BUTTON_H_ */
