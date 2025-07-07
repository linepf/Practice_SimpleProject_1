################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_Code/user_main/UART.c \
../User_Code/user_main/interrupt.c \
../User_Code/user_main/user_main.c 

OBJS += \
./User_Code/user_main/UART.o \
./User_Code/user_main/interrupt.o \
./User_Code/user_main/user_main.o 

C_DEPS += \
./User_Code/user_main/UART.d \
./User_Code/user_main/interrupt.d \
./User_Code/user_main/user_main.d 


# Each subdirectory must supply rules for building sources it contributes
User_Code/user_main/%.o User_Code/user_main/%.su User_Code/user_main/%.cyclo: ../User_Code/user_main/%.c User_Code/user_main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/GitHub/practice_SimpleProject_1/practice_SimpleProject_1/User_Code/IOport" -I"E:/GitHub/practice_SimpleProject_1/practice_SimpleProject_1/User_Code/user_main" -I"E:/GitHub/practice_SimpleProject_1/practice_SimpleProject_1/User_Code/dev" -I"E:/GitHub/practice_SimpleProject_1/practice_SimpleProject_1/User_Code/common" -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User_Code-2f-user_main

clean-User_Code-2f-user_main:
	-$(RM) ./User_Code/user_main/UART.cyclo ./User_Code/user_main/UART.d ./User_Code/user_main/UART.o ./User_Code/user_main/UART.su ./User_Code/user_main/interrupt.cyclo ./User_Code/user_main/interrupt.d ./User_Code/user_main/interrupt.o ./User_Code/user_main/interrupt.su ./User_Code/user_main/user_main.cyclo ./User_Code/user_main/user_main.d ./User_Code/user_main/user_main.o ./User_Code/user_main/user_main.su

.PHONY: clean-User_Code-2f-user_main

