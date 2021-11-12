################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../ECU1.c \
../ICU.c \
../applicarionMCU1.c \
../keypad.c \
../lcd.c \
../timers.c \
../uart.c 

OBJS += \
./ADC.o \
./ECU1.o \
./ICU.o \
./applicarionMCU1.o \
./keypad.o \
./lcd.o \
./timers.o \
./uart.o 

C_DEPS += \
./ADC.d \
./ECU1.d \
./ICU.d \
./applicarionMCU1.d \
./keypad.d \
./lcd.d \
./timers.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


