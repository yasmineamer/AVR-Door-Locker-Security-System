/*
 * ECU1.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Yasmine Amer
 */

#ifndef ECU1_H_
#define ECU1_H_

#include "timers.h"
//#include "ADC.h"
//#include "ICU.h"

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include <util/delay.h>

#define pass_length 5
#define READY 10
#define NOT_READY 0
#define IF_PW_MATCHED 7
#define MAX_TRY 3
#define WRONG 0
#define DONE 1

typedef enum{
	INITIAL = 2,
	CHG_PW,
	O_DOOR,
	ERROR
}STATE;

typedef enum {
	UNMATCHED,
	MATCHED
}CHECK;


/*
 * Description: A function that's responsible for initializing all the required
 * Modules that are used in the Human Machine Interface ECU
 */
void modules_init (void);
void system_mainMenu(void);
void Timer1_setup (timer_config * config_ptr);
void openFlag (void);
void closeFlag (void);
void user_setPW (void);
void user_confirmPW(void);
CHECK System_checkMatching(void);
void system_errorMessage (void);
void system_confirmSavePW (void);
STATE userChooseOption(void);
void systemConfirmOpenClose(void);
void systemClose (void);
CHECK userEnterPW (void);

#endif /* ECU1_H_ */
