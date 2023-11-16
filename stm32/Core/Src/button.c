/*
 * button.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Truc Le
 */


#include "button.h"

uint16_t pinBuffer[NUM_OF_BUTTON] = { BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin};

// define the buffer storing current states of buttons
static GPIO_PinState buttonBuffer[NUM_OF_BUTTON];

// define two buffers for debouncing
static GPIO_PinState buttonReg1[NUM_OF_BUTTON];
static GPIO_PinState buttonReg2[NUM_OF_BUTTON];
static GPIO_PinState buttonReg3[NUM_OF_BUTTON];

static uint8_t flagForButtonPressed[NUM_OF_BUTTON];

int counterForButton2Hold = 0;

void button_reading()
{
	for(int i = 0; i < NUM_OF_BUTTON; i++)
	{
		buttonReg1[i] = buttonReg2[i];
		buttonReg2[i] = buttonBuffer[i];
		buttonBuffer[i] = HAL_GPIO_ReadPin(GPIOB, pinBuffer[i]);

		if((buttonReg1[i] == buttonReg2[i]) && (buttonReg2[i] == buttonBuffer[i]))
		{
			if(buttonReg3[i] != buttonBuffer[i])
			{
				buttonReg3[i] = buttonBuffer[i];
				if(buttonBuffer[i] == PRESSED_STATE)
				{
					// set flag for the button
					flagForButtonPressed[i] = 1;
					// set counter for button2 if it's being hold
					if(i == 1) counterForButton2Hold = DURATION_FOR_AUTO_INCREASING;
				}
			} else {
				// we just need to process hold condition for button2
				// start counting for button2 that is being hold
				if((counterForButton2Hold > 0))
				{
					counterForButton2Hold--;
					if (counterForButton2Hold == 0 && buttonBuffer[1] == PRESSED_STATE){
						// set flag for button2 and reset counter
						flagForButtonPressed[1] = 1;
						counterForButton2Hold = DURATION_FOR_AUTO_INCREASING;
					}
				}
			}
		}
	}
}

int isbuttonPressed(int index)
{
	// make sure index > 0 && index < NUM_OF_BUTTON
	if(flagForButtonPressed[index] == 1)
	{
		flagForButtonPressed[index] = 0;\
		resetAllFlag();
		return 1;
	}

	return 0;
}

void resetAllFlag()
{
	for (int i = 0; i < NUM_OF_BUTTON; ++i) {
		flagForButtonPressed[i] = 0;
	}
}
