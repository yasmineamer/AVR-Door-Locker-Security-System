/*
 * timers.c
 *
 *  Created on: Oct 2, 2020
 *      Author: Yasmine Amer
 */

#include "timers.h"
static void (*g_CallBackPtr)(void) = NULL_PTR;

#define timer1

static void (*g_CallBackPtr_chB)(void) = NULL_PTR;
static void (*g_CallBackPtr_chA)(void) = NULL_PTR;



#ifdef timer0
static void (*g_CallBackPtr0)(void) = NULL_PTR;
/* delay function using timer0 */
/* no. of cycles = 0xff - initiate_timer + 1 cycle roll over to raise TOV0 flag  */
/*total delay = no.of cycle * Time of one tick*/
void delay (const timer_config * config_ptr)
{
	TCNT0 = config_ptr -> init_timer ;
	TCCR0 = (1 << FOC0) | ((config_ptr -> timerClk)& 0x07) ;/* normal mode, Prescaling F_CPU CLK  */
	while (BIT_IS_CLEAR(TIFR,TOV0));/*waiting until overflow occurs  */
	TCCR0 = 0; /*turn off timer0*/
	TIFR  = SET_BIT(TIFR, TOV0);/*clear flag by writing one on it*/

}

/*timer0 overflow interrupt handled by ISR */

void timer0_ovf_init(const timer_config * config_ptr)
{
	TCNT0 = config_ptr -> init_timer ; //set the initial value of timer counter register
	TCCR0 = (1 << FOC0) | ((config_ptr -> timerClk)& 0x07);
	TIMSK = (1<<TOIE0);/* ENABLE TIMER0 OVERFLOW INTERRUPT */

}

/*timer0 CTC mode + interrupt handled by ISR */

void timer0_ctc_init(const timer_config * config_ptr , uint8 compare_match)
{

	TCNT0 = config_ptr -> init_timer ;
	TCCR0 = (1 << FOC0) | (1 << WGM01) |(1<<COM01) | ((config_ptr -> timerClk)& 0x07);
	OCR0  = compare_match;
	TIMSK = (1<< OCR0);/* ENABLE TIMER0 Compare match INTERRUPT */
}

/* timer0 generating fast pwm non_inverting mode*/
void PWM_init(const timer_config * config_ptr)
{
	TCNT0 = config_ptr -> init_timer ; /*initiate timer0*/
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | ((config_ptr -> timerClk)& 0x07);/*fast pwm, non_inerting and prescaler*/
	DDRB |= (1 << PB3); /*set oco pin as output pin */
}

void set_duty (uint8 duty)
{
	OCR0 =duty;
}


/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void (*a_ptr)(void))
{
	g_CallBackPtr0 = a_ptr ;
}


ISR(TIMER0_OVF_vect)
{
	if(g_CallBackPtr0 != NULL_PTR)
	{
		(*g_CallBackPtr0)();
	}

}
ISR(TIMER0_COMP_vect)
{
	if(g_CallBackPtr0 != NULL_PTR)
	{
		(*g_CallBackPtr0)();
	}

}
void timer0_deinit (void)
{
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0  = 0;
	TIMSK &= ~(1<<OCIE0) & (~(1<<TOIE0));
}


#endif




#ifdef timer2
static void (*g_CallBackPtr2)(void) = NULL_PTR;
/* delay function using timer2 */
/* no. of cycles = 0xff - initiate_timer + 1 cycle roll over to raise TOV0 flag  */
/*total delay = no.of cycle * Time of one tick*/
void TIMER2_delay (timer_config * config_ptr)
{
	TCNT2  = config_ptr -> init_timer ;
	TCCR2 = (1 << FOC2) | ((config_ptr -> timerClk)& 0x07) ;/* normal mode, Prescaling F_CPU CLK  */
	while (BIT_IS_CLEAR(TIFR,TOV2));/*waiting until overflow occurs  */
	TCCR2 = 0; /*turn off timer2*/
	TIFR  = SET_BIT(TIFR, TOV2);/*clear flag by writing one on it*/

}

/*timer2 overflow interrupt handled by ISR */

void timer2_ovf_init(timer_config * config_ptr)
{
	TCNT2 = config_ptr -> init_timer ;
	TCCR2 = (1 << FOC2) | ((config_ptr -> timerClk)& 0x07);
	TIMSK = (1<<TOIE2);/* ENABLE TIMER2 OVERFLOW INTERRUPT */

}

/*timer2 CTC mode + interrupt handled by ISR */

void timer2_ctc_init(timer_config * config_ptr , uint8 compare_match)
{

	TCNT2 = config_ptr -> init_timer ;
	TCCR2 = (1 << FOC2) | (1 << WGM21) |(1<<COM21) | ((config_ptr -> timerClk)& 0x07);
	OCR2  = compare_match;
	TIMSK = (1<< OCR2);/* ENABLE TIMER2 Compare match INTERRUPT */
}

/* timer2 generating fast pwm non_inverting mode*/
void TIMER2_PWM_init(timer_config * config_ptr)
{
	TCNT2 = config_ptr -> init_timer ; /*initiate timer0*/
	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | ((config_ptr -> timerClk)& 0x07);/*fast pwm, non_inerting and prescaler*/
	DDRD |= (1 << PD7); /*set oc2 pin as output pin */
}

void TIMER2_set_duty (uint8 duty)
{
	OCR2 =duty;
}

ISR(TIMER2_OVF_vect)
{
	if(g_CallBackPtr2 != NULL_PTR)
	{
		(*g_CallBackPtr2)();
	}

}
ISR(TIMER2_COMP_vect)
{
	if(g_CallBackPtr2 != NULL_PTR)
	{
		(*g_CallBackPtr2)();
	}

}



#endif

#ifdef timer1
/* delay function using timer1 */
/* no. of cycles = 0xff - initiate_timer + 1 cycle roll over to raise TOV0 flag  */
/*total delay = no.of cycle * Time of one tick*/
void TIMER1_delay (const timer_config * config_ptr)
{
	TCNT1  = config_ptr -> init_timer ;
	TCCR1A = (1 << FOC1A)|(1 << FOC1B);/* normal mode */
	TCCR1B = ((config_ptr -> timerClk)& 0x07); /*prescaler*/
	while (BIT_IS_CLEAR(TIFR,TOV1));/*waiting until overflow occurs  */
	TCCR1B = 0; /*turn off timer1*/
	TIFR  = SET_BIT(TIFR, TOV1);/*clear flag by writing one on it*/

}
/*timer1 overflow interrupt handled by ISR */

void timer1_ovf_init(const timer_config * config_ptr)
{
	TCNT1 = config_ptr -> init_timer ;
	TCCR1A = (1 << FOC1A)|(1 << FOC1B);/* normal mode */
	TCCR1B = ((config_ptr -> timerClk)& 0x07); /*prescaler*/
	TIMSK |= (1<<TOIE1);/* ENABLE TIMER1 OVERFLOW INTERRUPT */

}

/*timer1 CTC mode + interrupt handled by ISR */
/*channel A*/

void timer1_ctc_chA_init(const timer_config * config_ptr , uint16 compare_matchA)
{

	TCNT1 = config_ptr -> init_timer ;
	TCCR1A = (1 << FOC1A)|(1 << FOC1B) | (1 << COM1A1);/*clear on compare match */
	OCR1A  = compare_matchA;
	TIMSK |= (1<< OCIE1A);/* ENABLE TIMER1 Compare match INTERRUPT */
	TCCR1B = ( 1 << WGM12) | ((config_ptr -> timerClk)& 0x07); /*ctc ,prescaler*/
}

/*timer1 CTC mode + interrupt handled by ISR */
/*channel B*/
void timer1_ctc_chB_init(const timer_config * config_ptr , uint16 compare_matchB)
{

	TCNT1 = config_ptr -> init_timer ;
	TCCR1A = (1 << FOC1A)|(1 << FOC1B) | (1 << COM1B1);/*clear on compare match */
	TCCR1B = ( 1 << WGM12) | ((config_ptr -> timerClk)& 0x07); /*ctc ,prescaler*/
	OCR1A  = compare_matchB;
	TIMSK |= (1<<OCIE1B);/* ENABLE TIMER1 Compare match INTERRUPT */
}


/* timer1 generating fast pwm non_inverting mode*/

void TIMER1_PWM_init(const timer_config * config_ptr)
{
	TCNT1  = config_ptr -> init_timer ;
	TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);/*clear on compare match non inverting mode */
	TCCR1B = ( 1 << WGM12) | ( 1 << WGM13) | ((config_ptr -> timerClk)& 0x07); /*fast pwm, prescaler*/
	DDRD |= (1 << PD5);/* set pin PD5 as output pin*/
}

/*this two function can be written in the main */
/*
 * Description: Function to set the value of OCR1A.
 */
void set_duty_ChannelA (uint16 duty)
{
	OCR1A =duty;/*pwm max OCR1A if i want to generate two pwm load OCR1B with the smaller value */
}
/*
 * Description: Function to set the value of OCR1B.
 */
void set_duty_ChannelB (uint16 duty)
{
	OCR1B =duty;
}

/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBackOvf(void (*a_ptr)(void))
{
	g_CallBackPtr = a_ptr ;
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBackChA(void(*a_ptr)(void))
{
	g_CallBackPtr_chA = a_ptr ;
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBackChB(void(*a_ptr)(void))
{
	g_CallBackPtr_chB = a_ptr ;
}



ISR(TIMER1_OVF_vect)
{
	if(g_CallBackPtr != NULL_PTR)
	{
		(*g_CallBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_CallBackPtr_chA != NULL_PTR)
	{
		(*g_CallBackPtr_chA)();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_CallBackPtr_chB != NULL_PTR)
	{
		(*g_CallBackPtr_chB)();
	}
}

void timer1_deinit (void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A  = 0;
	OCR1B  = 0;
	TIMSK &= ~(1<<OCIE1A) & (~(1<<OCIE1B));
}
#endif
