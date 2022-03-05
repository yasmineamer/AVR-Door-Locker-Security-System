/*
 * timers.h
 *
 *  Created on: Oct 2, 2020
 *      Author: Y
 */


#ifndef TIMERS_H_
#define TIMERS_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define timer1
#define channelA

#define NULL_PTR (void*)0

typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_CLOCK_8,
	F_CPU_CLOCK_64,
	F_CPU_CLOCK_256,
	F_CPU_CLOCK_1024,
	EXTERNAL_CLK_FALLING_EDGE,
	EXTERNAL_CLK_RAISING_EDGE
}TIMER_CLK;

typedef struct
{
	uint16 init_timer;
	TIMER_CLK timerClk;
}timer_config ;

/**********************************************FUNCTION PROTOTYPES************************************************/
                  /*********************************TIMER1***********************************/
void TIMER1_delay (const timer_config * config_ptr);
void timer1_ovf_init(const timer_config * config_ptr);
void timer1_ctc_chA_init(const timer_config * config_ptr , uint16 compare_matchA);
void timer1_ctc_chB_init(const timer_config * config_ptr , uint16 compare_matchB);
void TIMER1_PWM_init(const timer_config * config_ptr);
void set_duty_ChannelA ( uint16 duty);
void set_duty_ChannelB ( uint16 duty);

void Timer1_setCallBackOvf(void(*a_ptr)(void));
void Timer1_setCallBackChA(void(*a_ptr)(void));
void Timer1_setCallBackChB(void(*a_ptr)(void));

void timer1_deinit (void);

               /***********************************TIMER2***********************************/
void TIMER2_delay (timer_config * config_ptr);
void timer2_ovf_init(timer_config * config_ptr);
void timer2_ctc_init(timer_config * config_ptr , uint8 compare_match);
void TIMER2_PWM_init(timer_config * config_ptr);
void TIMER2_set_duty (uint8 duty);


                /***********************************TIMER0***********************************/

void delay (const timer_config * config_ptr);
void timer0_ovf_init(const timer_config * config_ptr);
void timer0_ctc_init(const timer_config * config_ptr , uint8 compare_match);
void PWM_init(const timer_config * config_ptr);
void set_duty (uint8 duty);


#endif /* TIMERS_H_ */
