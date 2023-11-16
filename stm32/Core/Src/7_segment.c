/*
 * 7_segment.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Truc Le
 */


#include "7_segment.h"

uint16_t segments[7] = {SEG_A_Pin, SEG_B_Pin, SEG_C_Pin, SEG_D_Pin, SEG_E_Pin, SEG_F_Pin, SEG_G_Pin};
int led_buffer[4];
int led_index = 0;

void display_7SEG(int num)
{
		switch(num)
		{
			case 0:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[1] | segments[2] | segments[3] | segments[4] | segments[5], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[6], SET);
				break;
			case 1:
				HAL_GPIO_WritePin(GPIOA, segments[1] | segments[2], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[3] | segments[4] | segments[5] | segments[6], SET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[1] | segments[3] | segments[4] | segments[6], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[2] | segments[5], SET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[1] | segments[3] | segments[2] | segments[6], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[4] | segments[5], SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOA, segments[1] | segments[2] | segments[5] | segments[6], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[4] | segments[0] | segments[3], SET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[5] | segments[3] | segments[2] | segments[6], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[4] | segments[1], SET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[6] | segments[2] | segments[3] | segments[4] | segments[5], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[1], SET);
				break;
			case 7:
				HAL_GPIO_WritePin(GPIOA, segments[3] | segments[4] | segments[5] | segments[6], SET);
				HAL_GPIO_WritePin(GPIOA, segments[1] | segments[0] | segments[2], RESET);
				break;
			case 8:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[1] | segments[2] | segments[3] | segments[4] | segments[5] | segments[6], RESET);
				break;
			case 9:
				HAL_GPIO_WritePin(GPIOA, segments[0] | segments[1] | segments[2] | segments[3] | segments[6] | segments[5], RESET);
				HAL_GPIO_WritePin(GPIOA, segments[4], SET);
				break;
		}
}

void scan7sSEG()
{
	updateClockBuffer();

	// scan 4 7 segments leds
	if(timer1_flag)
	{
	  update7SEG(led_index);
	  led_index++;
	  if(led_index >= MAX_LED)
	  {
		  led_index = 0;
	  }
	  setTimer1(scan_duration);
	}
//	display_7SEG(road2_counter);
}

void updateClockBuffer()
{
	led_buffer[0] = road1_counter / 10;
	led_buffer[1] = road1_counter % 10;

	led_buffer[2] = road2_counter / 10;
	led_buffer[3] = road2_counter % 10;
}

void update7SEG(int index)
{
	switch (index) {
		case 0:
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN3_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, EN0_Pin, RESET);

			display_7SEG(led_buffer[index]);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, EN0_Pin | EN2_Pin | EN3_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, EN1_Pin, RESET);

			display_7SEG(led_buffer[index]);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN3_Pin | EN0_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, EN2_Pin, RESET);

			display_7SEG(led_buffer[index]);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN0_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, EN3_Pin, RESET);

			display_7SEG(led_buffer[index]);
			break;
		default:
			break;
	}
}
