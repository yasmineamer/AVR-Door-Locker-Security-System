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
	timer1_ctc_chAB_init(config_ptr , 9770, 19532);
	Timer1_setCallBackChB(clockwise);
	Timer1_setCallBackChA(counterclockwise);

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

CHECK setReceivePW (void)
{
	uint8 password_1[pass_length+1];
	uint8 password_2[pass_length+1];
	CHECK check;


	while((UART_receiveByte ()) != READY);

	UART_receiveString (password_1);

	while((UART_receiveByte ()) != READY);

	UART_receiveString (password_2);

	if (strcmp (password_1,password_2) == 0)
	{
		check = MATCHED;
		storePW (password_1);
		UART_sendByte(READY);
		UART_sendByte (MATCHED);
	}

	else
	{
		check = UNMATCHED;
		UART_sendByte(READY);
		UART_sendByte (UNMATCHED);
	}
	return check;
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
	for (uint16 Idix=0 ; Idix<pass_length ; Idix++)
	{
		EEPROM_writeByte (Idix,password_1_Ptr[Idix]);
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

CHECK checkMatch (void)
{
	uint8 Idix;
	uint8 password[pass_length+1];
	uint8 stored_password[pass_length+1];
	CHECK check;
	while ((UART_receiveByte ()) != READY);
	UART_receiveString (password);
	for(Idix=0 ; Idix<pass_length ; Idix++)
    {
     	EEPROM_readByte(Idix,&stored_password[Idix]);
     	_delay_ms(5);
    }
	stored_password[Idix] = '\0';

	if ((strcmp (password,stored_password)) == 0)
		{
			while ((UART_receiveByte ()) != READY);
			UART_sendByte(READY);
			UART_sendByte (MATCHED);
			check = MATCHED;
			return check;
		}
	else
	{
		while ((UART_receiveByte ()) != READY);
		UART_sendByte(READY);
		UART_sendByte (UNMATCHED);
		check = UNMATCHED;
		return check;
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
	while (1)
	{
		Toggle_buzzer ();
		_delay_ms (500);
	}
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

STATE getState (void)
{
	while ((UART_receiveByte ()) != READY);
	return ((UART_receiveByte ()));
}


void Toggle_buzzer (void)
{
    TOGGLE_BIT (PORTD,PD7);
}
