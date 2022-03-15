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
#include "uart.h"
#include <string.h>
#include <util/delay.h>
#include "motor.h"
#include "external_eeprom.h"
//#include "i2c.h"

#define pass_length 5
#define READY 100


#define MAX_TRY 3

typedef enum{
	INITIAL = 2,
	CHG_PW,
	O_DOOR,
	IDLE
}STATE;

typedef enum {
	UNMATCHED=10,
	MATCHED
}CHECK;


/****************************************Functions prototype***********************************************/

void setReceivePW (void);
void clockwise (void);
void counterclockwise (void);
void getState (void);
void Toggle_buzzer (void);
void MOTOR_stop (void);
void MOTOR_close (void);
void MOTOR_open (void);
void alert (void);
void checkMatch (void);
void sendCheck (void);
void storePW (uint8 *password_1_Ptr);
void setReceivePW (void);
void Timer1_setup (timer_config * config_ptr);
void MODULES_init (void);
#endif /* ECU2_H_ */
