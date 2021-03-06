/*
 * motor.h
 *
 *  Created on: Nov 20, 2021
 *      Author: Yasmine Amer
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Motor HW Pins */
#define MOTOR_DIR DDRB
#define MOTOR_PORT PORTB
#define MOTOR_PIN_A PB0
#define MOTOR_PIN_B PB1
#define CLOCKWISE 80
#define ANTICLOCKWISE 81

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void motor_init (void);
void MOTOR_dir (uint8);
void MOTOR_deinit (void);


#endif /* MOTOR_H_ */
