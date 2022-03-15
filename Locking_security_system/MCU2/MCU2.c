/*
 * MCU2.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Yasmine Amer
 */


#include "MCU2.h"
#include "ECU2.h"
#include "timers.h"

	extern volatile STATE state ;
	extern volatile CHECK check ;
	uint8 error_entry = 0;
int main (void)
{
	timer_config timer1_config = {0,F_CPU_CLOCK_1024}; // overflow after 67s
	MODULES_init();

	while(1)
	{
		Toggle_buzzer ();
		_delay_ms (200);
		Toggle_buzzer ();

		getState();
		check = UNMATCHED ;

		while(state == INITIAL && check == UNMATCHED)
		{
			setReceivePW();
			sendCheck();
		}

		if (state == CHG_PW)
		{
			check = UNMATCHED;
			error_entry = 0 ;
			while(check == UNMATCHED && error_entry < MAX_TRY)
			{
				checkMatch();
				sendCheck();

				error_entry ++;

			}

			if(error_entry < MAX_TRY)
			{
				error_entry = 0;
				check = UNMATCHED;
				while(check == UNMATCHED && error_entry < MAX_TRY)
				{
					setReceivePW();
					sendCheck();
					error_entry ++;
				}
			}
			else if (error_entry >= MAX_TRY)
			{
				alert();
			}
		}

		else if(state == O_DOOR )
		{
			check = UNMATCHED;
			error_entry = 0;
			while(check == UNMATCHED && error_entry < MAX_TRY)
			{
				checkMatch();
				sendCheck();
				error_entry ++;

			}

			if(error_entry < MAX_TRY)
			{
				error_entry = 0;
				Timer1_setup (&timer1_config);
				MOTOR_open();
				Timer1_setCallBackChA(counterclockwise);
				MOTOR_stop();
			}
			else if(error_entry >= MAX_TRY)
			{
				alert();
			}
		}

	}
}
