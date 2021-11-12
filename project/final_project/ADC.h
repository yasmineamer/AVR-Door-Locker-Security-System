/*
 * ADC.h
 *
 *  Created on: Sep 23, 2020
 *      Author: Y
 *
 */

#ifndef ADC_H_
#define ADC_H_

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"

#define NULL_PTR (void*)0

/***Global variable DECLARTION***/

volatile uint16 g_adcResult;

/**ADC STD_TYPES**/

typedef enum {
	DISABLE , ENABLE
}ADC_INT;

typedef enum {
	AREF,AVCC,RESVERVED,INTERNAL_VREF
}V_REF;

typedef enum {
	F_CPU_2_0, F_CPU_2_1 ,F_CPU_4 ,F_CPU_8, F_CPU_16 ,F_CPU_32 ,F_CPU_64 ,F_CPU_128
}ADC_CLOCK;

typedef struct {
	V_REF vref;
	ADC_INT interrupt;
	ADC_CLOCK clk;

}ADC_configType;

/******* FUNCTION PROTOTYBE ******/
void ADC_init(const ADC_configType *config_ptr);

void ADC_readChannel(uint8 channel_num );

#endif /* ADC_H_ */
