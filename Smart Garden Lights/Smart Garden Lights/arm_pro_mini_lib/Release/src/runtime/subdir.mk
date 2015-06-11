################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/runtime/cr_cpp_config.cpp \
../src/runtime/cr_startup_lpc11uxx.cpp 

C_SRCS += \
../src/runtime/sysinit.c 

OBJS += \
./src/runtime/cr_cpp_config.o \
./src/runtime/cr_startup_lpc11uxx.o \
./src/runtime/sysinit.o 

C_DEPS += \
./src/runtime/sysinit.d 

CPP_DEPS += \
./src/runtime/cr_cpp_config.d \
./src/runtime/cr_startup_lpc11uxx.d 


# Each subdirectory must supply rules for building sources it contributes
src/runtime/%.o: ../src/runtime/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/runtime/%.o: ../src/runtime/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -D__NEWLIB__ -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


