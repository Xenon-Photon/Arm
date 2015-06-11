################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/usb_serial/usb_serial.cpp 

C_SRCS += \
../src/usb_serial/cdc_desc.c \
../src/usb_serial/cdc_vcom.c 

OBJS += \
./src/usb_serial/cdc_desc.o \
./src/usb_serial/cdc_vcom.o \
./src/usb_serial/usb_serial.o 

C_DEPS += \
./src/usb_serial/cdc_desc.d \
./src/usb_serial/cdc_vcom.d 

CPP_DEPS += \
./src/usb_serial/usb_serial.d 


# Each subdirectory must supply rules for building sources it contributes
src/usb_serial/%.o: ../src/usb_serial/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -U__cplusplus -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usb_serial/%.o: ../src/usb_serial/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -I"C:\Users\mido2008\Documents\LPCXpresso_7.6.2_326\workspace2\arm_pro_mini_lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


