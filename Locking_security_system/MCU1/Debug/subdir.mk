################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECU1.c \
../applicarionMCU1.c \
../keypad.c \
../lcd.c \
../timers.c \
../uart.c 

OBJS += \
./ECU1.o \
./applicarionMCU1.o \
./keypad.o \
./lcd.o \
./timers.o \
./uart.o 

C_DEPS += \
./ECU1.d \
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


