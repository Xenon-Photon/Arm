################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/chip/adc_1125.c \
../src/chip/adc_11xx.c \
../src/chip/chip_11xx.c \
../src/chip/clock_11xx.c \
../src/chip/gpio_11xx_1.c \
../src/chip/gpio_11xx_2.c \
../src/chip/gpiogroup_11xx.c \
../src/chip/i2c_11xx.c \
../src/chip/i2cm_11xx.c \
../src/chip/iocon_11xx.c \
../src/chip/pinint_11xx.c \
../src/chip/pmu_11xx.c \
../src/chip/ring_buffer.c \
../src/chip/ssp_11xx.c \
../src/chip/sysctl_11xx.c \
../src/chip/sysinit_11xx.c \
../src/chip/timer_11xx.c \
../src/chip/uart_11xx.c \
../src/chip/wwdt_11xx.c 

OBJS += \
./src/chip/adc_1125.o \
./src/chip/adc_11xx.o \
./src/chip/chip_11xx.o \
./src/chip/clock_11xx.o \
./src/chip/gpio_11xx_1.o \
./src/chip/gpio_11xx_2.o \
./src/chip/gpiogroup_11xx.o \
./src/chip/i2c_11xx.o \
./src/chip/i2cm_11xx.o \
./src/chip/iocon_11xx.o \
./src/chip/pinint_11xx.o \
./src/chip/pmu_11xx.o \
./src/chip/ring_buffer.o \
./src/chip/ssp_11xx.o \
./src/chip/sysctl_11xx.o \
./src/chip/sysinit_11xx.o \
./src/chip/timer_11xx.o \
./src/chip/uart_11xx.o \
./src/chip/wwdt_11xx.o 

C_DEPS += \
./src/chip/adc_1125.d \
./src/chip/adc_11xx.d \
./src/chip/chip_11xx.d \
./src/chip/clock_11xx.d \
./src/chip/gpio_11xx_1.d \
./src/chip/gpio_11xx_2.d \
./src/chip/gpiogroup_11xx.d \
./src/chip/i2c_11xx.d \
./src/chip/i2cm_11xx.d \
./src/chip/iocon_11xx.d \
./src/chip/pinint_11xx.d \
./src/chip/pmu_11xx.d \
./src/chip/ring_buffer.d \
./src/chip/ssp_11xx.d \
./src/chip/sysctl_11xx.d \
./src/chip/sysinit_11xx.d \
./src/chip/timer_11xx.d \
./src/chip/uart_11xx.d \
./src/chip/wwdt_11xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/chip/%.o: ../src/chip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -U__cplusplus -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


