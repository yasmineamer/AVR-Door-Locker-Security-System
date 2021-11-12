/*
 * ECU1.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Yasmine Amer
 */


#include "ECU1.h"

//uint8 g_ticksCount = 0;
uint8 open_flag = 0;
uint8 close_flag = 0;

/*
 * Description : initialize Modules needed to interface with user
 * enable global interrupt bit
 */

void modules_init (void)
{
	LCD_init();
	UART_init();
	SREG |= (1<<7);

}
/*
 * Description : initialize Timer1 CTC + set call back to required function
 */
void Timer1_setup (timer_config * config_ptr)
{
	timer1_ctc_chAB_init(config_ptr , 9770, 19532);
	Timer1_setCallBackChB(openFlag);
	Timer1_setCallBackChA(closeFlag);

}

/*
 * Description : these two functions changes the value of polling flags
 */
void openFlag (void)
{
	open_flag = 1;
}



void closeFlag (void)
{
	close_flag = 1;
}

/*
 * Description : responsible about set password by getting it from user , display it on LCD
 * and send it to the 2nd MCU
 *
 */

void user_setPW (void)
{
	static uint8 visits = 0;

	uint8 password_1[pass_length+2];

	uint8 i;
	if(visits == 0)
	{
		visits ++;
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString(" **WELCOME** ");
		_delay_ms(1000);
	}


	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Enter Password:  ");
	LCD_goToRowColumn(1,0);

	for(i = 0; i< pass_length ;i++)
	{
		password_1[i] = KeyPad_getPressedKey();

		LCD_intgerToString(password_1[i]);
		_delay_ms(100);
		LCD_goToRowColumn(1,i);
		LCD_displayCharacter('*');

	}

	password_1[i] = '#';
	i++;

	password_1[i] ='\0';

	do{
		UART_sendByte(READY);
	}while( UART_receiveByte() != READY);

	UART_sendString(password_1);

	LCD_clearScreen();

}
/*
 * Description : responsible about confirm password by getting it from user for second time
 *  display it on LCD
 * and send it to the 2nd MCU
 *
 */

void user_confirmPW (void)
{
	uint8 password_2[pass_length+2];
	uint8 i ;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "confirm Password:  ");
	LCD_goToRowColumn(1,0);

	for(i=0 ; i<pass_length ; i++)
	{
		password_2[i] = KeyPad_getPressedKey();

		LCD_intgerToString(password_2[i]);
		_delay_ms(100);
		LCD_goToRowColumn(1,i);
		LCD_displayCharacter('*');
	}

	password_2[i] = '#';
	i++;

	password_2[i] ='\0';

	do{
		UART_sendByte(READY);
	}while( UART_receiveByte() != READY);

	UART_sendString(password_2);

	LCD_clearScreen();

}

/******************************************************************************
 *
 * Function Name: SYSTEM_mainMenu
 *
 * Description: A function that's responsible for displaying the main menu screen
 * that has the system two main options
 * + : For Changing the system's password
 * - : To open the door
 *
 * Input: void
 * Output: void
 *
 *****************************************************************************/
void system_mainMenu (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+:Change PW");
	LCD_displayStringRowColumn(1,0,"-:Open Door");
}

/*
 * Description: send to second MCU ask for confirm the password if the two input passwords
 * are the same
 */
CHECK System_checkMatching (void)
{
	CHECK receive = UNMATCHED;
	do{
		UART_sendByte(READY);
	}while( UART_receiveByte() != READY);

//	UART_sendByte(IF_PW_MATCHED);

	receive = UART_receiveByte();

	if(receive != MATCHED)
	{
		system_errorMessage();
		return receive;
	}
	return receive;
}

/*
 * Description: function display error message to user
 * when the input password isn't right
 */
void system_errorMessage (void)
{
	LCD_clearScreen();
	LCD_displayString(" **INVALID** ");
	_delay_ms(500);

	LCD_sendCommand(0x08);
	_delay_ms(500);
	LCD_sendCommand(0x0C);
	_delay_ms(500);
	LCD_sendCommand(0x08);
	_delay_ms(500);
	LCD_sendCommand(0x0C);

	LCD_clearScreen();
}

void system_confirmSavePW (void)
{
	LCD_clearScreen();
	LCD_displayString("Your Password is");
	LCD_displayStringRowColumn(1,0,"Saved");
	_delay_ms(1000);

	LCD_clearScreen();
}

STATE userChooseOption (void)
{
	uint8 userInput ;

	userInput =  KeyPad_getPressedKey();

	if(userInput == '+')
	{
		UART_sendByte(READY);
		UART_sendByte(CHG_PW);
		return CHG_PW ;
	}
	else if(userInput == '-')
	{
		UART_sendByte(READY);
		UART_sendByte(O_DOOR);
		return  O_DOOR ;
	}

	return ERROR;
}

void systemConfirmOpenClose(void)
{
	LCD_clearScreen();
	LCD_displayString("DOOR is OPEN");
	while(open_flag == 0);
	systemClose();
}

void systemClose (void)
{
	LCD_clearScreen();
	LCD_displayString("DOOR is OPEN");
	while(close_flag == 0);
	timer1_deinit();
}

CHECK userEnterPW(void)
{
	LCD_clearScreen();
	LCD_displayString("Enter Password: ");
	LCD_goToRowColumn(1,0);

	uint8 i;
	uint8 password[pass_length +1];
	for(i=0 ; i<pass_length ; i++)
	{
		password[i] = KeyPad_getPressedKey();
		LCD_goToRowColumn(1,i);
		LCD_displayCharacter('*');
	}

	password[i] = '#';
	i++;

	password[i] ='\0';

	do{
		UART_sendByte(READY);
	}while( UART_receiveByte() != READY);

	UART_sendString(password);

	while(UART_receiveByte() != READY);

	return (UART_receiveByte());
}


