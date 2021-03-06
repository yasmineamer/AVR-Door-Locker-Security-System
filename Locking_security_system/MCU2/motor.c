/*
 * motor.c
 *
 *  Created on: Nov 20, 2021
 *      Author: Yasmine Amer
 */



#include "motor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void motor_init (void)
{
	SET_BIT (MOTOR_DIR,MOTOR_PIN_A); //output pin
	SET_BIT (MOTOR_DIR,MOTOR_PIN_B); // output pin
	CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_A);
	CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_B);
}

void MOTOR_dir (uint8 direction)
{
	/* Configure Motor to rotate in the required direction */
	if (direction == CLOCKWISE)
	{
		CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_A);
		SET_BIT (MOTOR_PORT,MOTOR_PIN_B);
	}
	else if (direction == ANTICLOCKWISE)
	{
		SET_BIT (MOTOR_PORT,MOTOR_PIN_A);
		CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_B);
	}
}

void MOTOR_deinit (void)
{
	CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_A);
	CLEAR_BIT (MOTOR_PORT,MOTOR_PIN_B);
}
