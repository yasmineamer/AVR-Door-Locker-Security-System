/*
 * ECU2.c
 *
 *  Created on: Nov 10, 2021
 *      Author: Yasmine Amer
 */




#include "string.h"
#include "ECU2.h"

volatile uint8 g_clockwiseFlag = 0;
volatile uint8 g_counterclockwiseFlag = 0;


volatile STATE state = IDLE;
volatile CHECK check = UNMATCHED ;
/******************************************************************************
 *
 * Function Name: MODULES_init
 *
 * Description: A function that's responsible for initializing all the required
 * Modules that are used in the Human Machine Interface ECU
 *
 * Input: void
 * Output: void
 *
 *****************************************************************************/

void MODULES_init (void)
{
	UART_init ();
	EEPROM_init ();
	motor_init();
	SREG |= (1<<7);
	SET_BIT (DDRD,PD7); //buzzer
	CLEAR_BIT (PORTD,PD7);
}



/*
 * Description : initialize Timer1 CTC + set call back to required function
 */
void Timer1_setup (timer_config * config_ptr)
{
	timer1_ctc_chA_init(config_ptr , 9770);
	Timer1_setCallBackChA(clockwise);
//	Timer1_setCallBackChA(counterclockwise);

}

/******************************************************************************
 *
 * Function Name: CONTROL_setRecievePassword
 *
 * Description: Function responsible for receiving both the initial and confirmation
 * Passwords sent from the The 1st ECU and storing them in temporary strings and
 * Check for a match. If they are matched, Store them in the External EEPROM.
 * If not, Keep waiting until the user enters a valid initial/confirmation passwords.
 *
 * Input: void
 * Output: uint8
 *
 ****************** ***********************************************************/

void setReceivePW (void)
{
	uint8 password_1[pass_length+1];
	uint8 password_2[pass_length+1];



	UART_sendByte(READY);

	UART_receiveString (password_1);


	UART_sendByte(READY);

	UART_receiveString (password_2);


	if ((strcmp ((char *)password_1,(char *)password_2)) == 0)
	{
		check = MATCHED;
//		strcpy(stored_password,password_1);
		storePW (password_1);
	}

	else
	{
		check = UNMATCHED;

	}

}

/******************************************************************************
 *
 * Function Name: CONTROL_storePassword
 *
 * Description: Function responsible for storing the password in the external EEPROM
 *
 * Input: uint8 *
 * Output: void
 *
 *****************************************************************************/


void storePW (uint8 *password_1_Ptr)
{
	int check = 1;
	for (uint16 Idix=0 ; Idix<pass_length ; Idix++)
	{
		check=EEPROM_writeByte (Idix,password_1_Ptr[Idix]);
		if(check == 0)
		{
			Toggle_buzzer ();
			_delay_ms (200);
			Toggle_buzzer ();
			_delay_ms (200);
			Toggle_buzzer ();
			_delay_ms (200);
			Toggle_buzzer ();
			_delay_ms (200);
			Toggle_buzzer ();
		}
		_delay_ms (10);
	}
}


/******************************************************************************
 *
 * Function Name: CONTROL_checkMatch
 *
 * Description: Function responsible for checking matches with any entered password
 * And the stored password in the EEPROM.
 *
 * Input: void
 * Output: uint8
 *
 *****************************************************************************/

void checkMatch (void)
{
	uint8 Idix;
	uint8 password[pass_length+1];
	uint8 stored_password[pass_length+1];


	UART_sendByte (READY);
	UART_receiveString (password);

	for(Idix=0 ; Idix<pass_length ; Idix++)
		{
			EEPROM_readByte(Idix,&stored_password[Idix]);
			_delay_ms(10);
		}

	stored_password[Idix] = '\0';

	if ((strcmp((char *)password,(char *)stored_password)) == 0)
		{
			check = MATCHED;
		}
	else
		{
			check = UNMATCHED;
		}
}


/******************************************************************************
 *
 * Function Name: CONTROL_alert
 *
 * Description: Function responsible for toggling the buzzer in the case
 * of a theft or breaking.
 *
 * Input: void
 * Output: void
 *
 *****************************************************************************/


void alert (void)
{
	uint8 counter = 0;
	while (counter == 50000)
	{
		Toggle_buzzer ();
		_delay_ms (200);
		counter ++;
	}
	counter = 0;
}

/******************************************************************************
 *
 * Function Name: MOTOR_<state>
 *
 * Description: Function responsible the motor mechanics, as it's either
 * Opening ---> CW Direction
 * Closing ---> CCW Direction
 * At Rest
 *
 * Input: void
 * Output: void
 *
 *****************************************************************************/

void MOTOR_open (void)
{
	MOTOR_dir (CLOCKWISE);

	while (g_clockwiseFlag == 0); /* Polling for 8 seconds until the door is opened */
	g_clockwiseFlag = 0;
}


void MOTOR_close (void)
{
	MOTOR_dir (ANTICLOCKWISE);
	while (g_counterclockwiseFlag == 0); /* Polling for 8 seconds until the door is closed */
	g_counterclockwiseFlag = 0;
}


void MOTOR_stop (void)
{
	MOTOR_deinit ();
}

void clockwise (void)
{
	g_clockwiseFlag = 1;
}

void counterclockwise (void)
{
	g_counterclockwiseFlag = 1;
}

/******************************************************************************
 *
 * Function Name: CONTROL_getState
 *
 * Description: Function responsible for receiving the state at which the ECU
 * Must operate in.
 *
 * Input: void
 * Output: uint8
 *
 *****************************************************************************/

void getState (void)
{
	UART_sendByte (READY);
	state = UART_receiveByte ();

}


void Toggle_buzzer (void)
{
    TOGGLE_BIT (PORTD,PD7);
}

void sendCheck (void)
{
	while((UART_receiveByte ()) != READY);

	UART_sendByte (check);
}
