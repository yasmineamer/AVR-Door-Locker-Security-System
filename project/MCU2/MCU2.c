/*
 * MCU2.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Yasmine Amer
 */


#include "MCU2.h"

int main (void)
{
	timer_config timer1_config = {0,F_CPU_CLOCK_1024}; // overflow after 67s
	MODULES_init();
	STATE state = INITIAL;
	CHECK check = UNMATCHED ;
	uint8 error_entry = 0;



	while(1)
	{
		check = UNMATCHED ;
		state = getState();

		while(state == INITIAL && check == UNMATCHED)
		{
			check = setReceivePW();
		}

		if (state == CHG_PW)
		{
			check = UNMATCHED;
			while(check == UNMATCHED && error_entry == MAX_TRY)
			{
				check = checkMatch();
				if (check == UNMATCHED)
				{
					error_entry ++;
				}
			}
			if(error_entry != MAX_TRY)
			{
				error_entry = 0;
				check = UNMATCHED;
				while(check == UNMATCHED)
				{
					check = setReceivePW();
				}
			}
			else if (error_entry == MAX_TRY)
			{
				alert();
			}
		}
		else if(state == O_DOOR )
		{
			check = UNMATCHED;
			while(check == UNMATCHED && error_entry != MAX_TRY)
			{
				check = checkMatch();
				if(check == UNMATCHED)
				{
					error_entry ++;
				}

			}
			if(error_entry != MAX_TRY)
			{
				error_entry =0;
				Timer1_setup (&timer1_config);
				MOTOR_open();
				MOTOR_stop();
			}
			else if(error_entry == MAX_TRY)
			{
				alert();
			}
		}

	}
}
