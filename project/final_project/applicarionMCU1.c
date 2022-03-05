/*
 * applicarionMCU1.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Yasmine amer
 */



#include "applicationMCU1.h"

	extern volatile STATE state ;
	extern volatile CHECK check ;
	extern volatile  uint8 NumOfTry ;

int main(void)
{


	timer_config timer1_config = {0,F_CPU_CLOCK_1024}; // overflow after 67s

	modules_init();



	while(1)
	{
		while(check == UNMATCHED && state == INITIAL)
		{
			sendState(state);
			user_setPW();
			user_confirmPW();
			System_checkMatching();
			if(check == MATCHED)
			{
				system_confirmSavePW();
			}
		}

		system_mainMenu();

		userChooseOption(); // get the option from user and send it to the MCU

		sendState(state);
		if(state == CHG_PW)
		{
			check = UNMATCHED;

			while(check == UNMATCHED)
			{
				userEnterPW();

				NumOfTry ++;
				if (NumOfTry >= MAX_TRY)
				{
					break;
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
					System_checkMatching();
					if(check == MATCHED)
					{
						system_confirmSavePW();
					}
					NumOfTry ++;
					if (NumOfTry >= MAX_TRY)
					{
						break;
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
			NumOfTry = 0;

			while(check == UNMATCHED)
			{
				userEnterPW();

				NumOfTry ++;
				if (NumOfTry >= MAX_TRY)
				{
					break;
				}
			}

			if (NumOfTry != MAX_TRY)
			{
				NumOfTry = 0;
				Timer1_setup (&timer1_config);
				systemConfirmOpenClose();
				Timer1_setCallBackChA(closeFlag);
				systemClose ();

			}
			else if (NumOfTry == MAX_TRY)
			{
				system_errorMessage();
				_delay_ms(5000);
			}
		}


	}


}
