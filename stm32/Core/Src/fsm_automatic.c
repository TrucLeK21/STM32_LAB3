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
			road1_counter = red_duration;
			road2_counter = green_duration;

			setTimer1(road2_counter*count_duration);
			setTimer2(count_duration);
			break;
		case RED1_GREEN2:
			red1_green2();

			// update counter for 7 Segments
			if(timer2_flag)
			{
				road1_counter--;
				road2_counter--;
				setTimer2(count_duration);
			}

			// update new status when timer1_flag == 1
			if(timer1_flag)
			{
				status = RED1_YELLOW2;
				road2_counter = yellow_duration;
				setTimer1(road2_counter*count_duration);
			}
			break;
		case RED1_YELLOW2:
			red1_yellow2();

			// update counter for 7 Segments
			if(timer2_flag)
			{
				road1_counter--;
				road2_counter--;
				setTimer2(count_duration);
			}

			// update new status when timer1_flag == 1
			if(timer1_flag)
			{
				status = GREEN1_RED2;
				road1_counter = green_duration;
				road2_counter = red_duration;
				setTimer1(road1_counter*count_duration);
			}
			break;
		case GREEN1_RED2:
			green1_red2();

			// update counter for 7 Segments
			if(timer2_flag)
			{
				road1_counter--;
				road2_counter--;
				setTimer2(count_duration);
			}

			// update new status when timer1_flag == 1
			if(timer1_flag)
			{
				status = YELLOW1_RED2;
				road1_counter = yellow_duration;
				setTimer1(road1_counter*count_duration);
			}
			break;
		case YELLOW1_RED2:
			yellow1_red2();

			// update counter for 7 Segments
			if(timer2_flag)
			{
				road1_counter--;
				road2_counter--;
				setTimer2(count_duration);
			}

			// update new status when timer1_flag == 1
			if(timer1_flag)
			{
				status = RED1_GREEN2;
				road1_counter = red_duration;
				road2_counter = green_duration;
				setTimer1(road2_counter*count_duration);
			}
			break;
		default:
			break;
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
