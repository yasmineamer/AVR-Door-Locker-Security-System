################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECU2.c \
../MCU2.c \
../external_eeprom.c \
../i2c.c \
../motor.c \
../timers.c \
../uart.c 

OBJS += \
./ECU2.o \
./MCU2.o \
./external_eeprom.o \
./i2c.o \
./motor.o \
./timers.o \
./uart.o 

C_DEPS += \
./ECU2.d \
./MCU2.d \
./external_eeprom.d \
./i2c.d \
./motor.d \
./timers.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


