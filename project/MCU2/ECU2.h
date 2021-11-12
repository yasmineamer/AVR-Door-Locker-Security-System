/*
 * ECU2.h
 *
 *  Created on: Nov 10, 2021
 *      Author: Yasmine Amer
 */

#ifndef ECU2_H_
#define ECU2_H_

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
#define READY 1
#define NOT_READY 0
#define IF_PW_MATCHED 7
#define MAX_TRY 3
#define WRONG 0
#define DONE 1

typedef enum{
	INITIAL = 1,
	CHG_PW,
	O_DOOR,
	ERROR
}STATE;

typedef enum {
	UNMATCHED,
	MATCHED
}CHECK;



#endif /* ECU2_H_ */
