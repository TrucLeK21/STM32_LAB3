/*
 * fsm_manual.c
 *
 *  Created on: Nov 15, 2023
 *      Author: trucle
 */


#include "fsm_manual.h"

int blinky_duration = 500;

void fsm_manual_run()
{
	switch (status) {
		case MAN_INIT:
			HAL_GPIO_WritePin(GPIOA, RED1_Pin | RED2_Pin | YELLOW1_Pin
					| YELLOW2_Pin | GREEN1_Pin | GREEN2_Pin, RESET);

			setTimer3(blinky_duration);
			status = MAN_RED;
			road1_counter = red_duration;

			// indicate mode 2
			road2_counter = 2;
			break;
		case MAN_RED:
			// led blinky
			man_red();
			// we will make use of road1_counter for display 7 segments LEDs and increasing time duration value
			if(isbuttonPressed(1)) road1_counter++;
			// set duration to temporary counter if button3 is pressed
			if(isbuttonPressed(2))
			{
				red_duration = road1_counter;
			}

			// switch to mode 3 when button two is pressed
			if(isbuttonPressed(0))
			{
				setTimer3(blinky_duration);
				status = MAN_YELLOW;
				road1_counter = yellow_duration;
				// turn off current state leds
				HAL_GPIO_WritePin(GPIOA, RED1_Pin | RED2_Pin, RESET);
				// indicate mode 3
				road2_counter = 3;
			}
			break;
		case MAN_YELLOW:
			// led blinky
			man_yellow();
			// we will make use of road1_counter for display 7 segments LEDs and increasing time duration value
			if(isbuttonPressed(1)) road1_counter++;
			// set duration to temporary counter if button3 is pressed
			if(isbuttonPressed(2))
			{
				yellow_duration = road1_counter;
			}

			// switch to mode 4 when button two is pressed
			if(isbuttonPressed(0))
			{
				setTimer3(blinky_duration);
				status = MAN_GREEN;
				road1_counter = green_duration;
				// turn off current state leds
				HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin | YELLOW2_Pin, RESET);
				// indicate mode 4
				road2_counter = 4;
			}
			break;
		case MAN_GREEN:
			// led blinky
			man_green();
			// we will make use of road1_counter for display 7 segments LEDs and increasing time duration value
			if(isbuttonPressed(1)) road1_counter++;
			// set duration to temporary counter if button3 is pressed
			if(isbuttonPressed(2))
			{
				green_duration = road1_counter;
			}

			// switch to mode 1 when button two is pressed
			if(isbuttonPressed(0))
			{
				if(red_duration == (yellow_duration + green_duration))
				{
					status = INIT;
				} else {
					// go back to mode 2 when the condition is not satisfied
					status = MAN_INIT;
				}
			}
			break;
		default:
			break;

		// check the limit
		if(road1_counter > 99)
		{
			road1_counter = 0;
		}
	}
}

void man_red()
{
	if(timer3_flag)
	{
		HAL_GPIO_TogglePin(GPIOA, RED1_Pin | RED2_Pin);
		setTimer3(blinky_duration);
	}
}

void man_yellow()
{
	if(timer3_flag)
	{
		HAL_GPIO_TogglePin(GPIOA, YELLOW1_Pin | YELLOW2_Pin);
		setTimer3(blinky_duration);
	}
}

void man_green()
{
	if(timer3_flag)
	{
		HAL_GPIO_TogglePin(GPIOA, GREEN1_Pin | GREEN2_Pin);
		setTimer3(blinky_duration);
	}
}
