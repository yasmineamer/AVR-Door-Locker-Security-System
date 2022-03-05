/*
 * MCU2.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Yasmine Amer
 */


#include "MCU2.h"
	extern volatile STATE state ;
	extern volatile CHECK check ;

int main (void)
{
	timer_config timer1_config = {0,F_CPU_CLOCK_1024}; // overflow after 67s
	MODULES_init();

	uint8 error_entry = 0;



	while(1)
	{
		check = UNMATCHED ;
		getState();

		while(state == INITIAL && check == UNMATCHED)
		{
			 setReceivePW();
		}

		if (state == CHG_PW)
		{
			check = UNMATCHED;
			while(check == UNMATCHED)
			{
				checkMatch();

				error_entry ++;
				if( error_entry >= MAX_TRY)
				{
					break;
				}

			}
			if(error_entry != MAX_TRY)
			{
				error_entry = 0;
				check = UNMATCHED;
				while(check == UNMATCHED)
				{
					setReceivePW();
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
			error_entry = 0;
			while(check == UNMATCHED)
			{
				checkMatch();

				error_entry ++;
				if( error_entry >= MAX_TRY)
				{
					break;
				}

			}
			if(error_entry != MAX_TRY)
			{
				error_entry =0;
				Timer1_setup (&timer1_config);
				MOTOR_open();
				Timer1_setCallBackChA(counterclockwise);
				MOTOR_stop();
			}
			else if(error_entry == MAX_TRY)
			{
				alert();
			}
		}

	}
}
