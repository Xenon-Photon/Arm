################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/arm_pro_mini.cpp \
../src/isp_button_monitor.cpp \
../src/system_time.cpp 

OBJS += \
./src/arm_pro_mini.o \
./src/isp_button_monitor.o \
./src/system_time.o 

CPP_DEPS += \
./src/arm_pro_mini.d \
./src/isp_button_monitor.d \
./src/system_time.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


