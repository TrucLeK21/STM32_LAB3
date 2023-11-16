/*
 *
 * fsm_automatic.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */


#include "fsm_automatic.h"


int count_duration = 1000;

void fsm_automatic_run()
{
	switch (status) {
		case INIT:
			HAL_GPIO_WritePin(GPIOA, RED1_Pin | GREEN1_Pin | YELLOW1_Pin |
					RED2_Pin | YELLOW2_Pin | GREEN2_Pin, RESET);

			status = RED1_GREEN2;
			led_index = 0;
			road1_counter = red_duration;
			road2_counter = green_duration;

			setTimer1(scan_duration);
			setTimer2(count_duration);
			break;
		case RED1_GREEN2:
			red1_green2();

			if(road2_counter == 0)
			{
				status = RED1_YELLOW2;
				road2_counter = yellow_duration;
			}
			break;
		case RED1_YELLOW2:
			red1_yellow2();

			if(road1_counter == 0 && road2_counter == 0)
			{
				status = GREEN1_RED2;
				road1_counter = green_duration;
				road2_counter = red_duration;
			}
			break;
		case GREEN1_RED2:
			green1_red2();

			if(road1_counter == 0)
			{
				status = YELLOW1_RED2;
				road1_counter = yellow_duration;
			}
			break;
		case YELLOW1_RED2:
			yellow1_red2();

			if(road2_counter == 0 && road1_counter == 0)
			{
				status = RED1_GREEN2;
				road1_counter = red_duration;
				road2_counter = green_duration;
			}
			break;
		default:
			break;
	}

	scan7sSEG();

	// when the system is in automatic mode
	if(status < MAN_INIT)
	{
		// decrease the counter displaying on the 7 segments leds
		if(timer2_flag)
		{
			road1_counter--;
			road2_counter--;
			setTimer2(1000);
		}

		// check if it switch to mode 1
		if(isbuttonPressed(0))
		{
			status = MAN_INIT;
		}
	}
}

void red1_yellow2()
{
	HAL_GPIO_WritePin(GPIOA, RED1_Pin | YELLOW2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin | GREEN1_Pin | RED2_Pin | GREEN2_Pin, RESET);
}

void red1_green2()
{
	HAL_GPIO_WritePin(GPIOA, RED1_Pin | GREEN2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin | GREEN1_Pin | RED2_Pin | YELLOW2_Pin, RESET);
}

void yellow1_red2()
{
	HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin | RED2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, RED1_Pin | GREEN1_Pin | YELLOW2_Pin | GREEN2_Pin, RESET);
}

void green1_red2()
{
	HAL_GPIO_WritePin(GPIOA, GREEN1_Pin | RED2_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, RED1_Pin | YELLOW1_Pin | YELLOW2_Pin | GREEN2_Pin, RESET);
}
