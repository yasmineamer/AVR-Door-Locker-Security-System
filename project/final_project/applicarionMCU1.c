/*
 * applicarionMCU1.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Yasmine amer
 */



#include "applicationMCU1.h"


int main(void)
{
	STATE state = INITIAL;
	CHECK check = UNMATCHED;
	uint8 NumOfTry = 0;

	timer_config timer1_config = {0,F_CPU_CLOCK_1024}; // overflow after 67s

	modules_init();



	while(1)
	{
		while(check == UNMATCHED && state == INITIAL)
		{
			user_setPW();
			user_confirmPW();
			check = System_checkMatching();
			if(check == MATCHED)
			{
				system_confirmSavePW();
			}
		}

		system_mainMenu();

		state = userChooseOption(); // get the option from user and send it to the MCU

		if(state == CHG_PW)
		{
			check = UNMATCHED;

			while(check == UNMATCHED && NumOfTry == MAX_TRY)
			{
				check = userEnterPW();
				if( check == UNMATCHED)
				{
					NumOfTry ++;
				}
			}

			if(NumOfTry != MAX_TRY)
			{
				NumOfTry = 0;
				check = UNMATCHED ;

				while( check == UNMATCHED )
				{

					user_setPW();
					user_confirmPW();
					check = System_checkMatching();
					if(check == MATCHED)
					{
						system_confirmSavePW();
					}
				}
			}
			else if(NumOfTry == MAX_TRY)
			{
				system_errorMessage ();
				_delay_ms(5000);
			}
		}
		else if(state == O_DOOR)
		{
			check = UNMATCHED ;

			while(check == UNMATCHED && NumOfTry == MAX_TRY)
			{
				check = userEnterPW();
				if( check == UNMATCHED)
				{
					NumOfTry ++;
				}
			}

			if (NumOfTry != MAX_TRY)
			{
				NumOfTry = 0;
				Timer1_setup (&timer1_config);
				systemConfirmOpenClose();

			}
			else if (NumOfTry == MAX_TRY)
			{
				system_errorMessage();
				_delay_ms(5000);
			}
		}

		else
		{

			system_errorMessage();
		}


	}


}