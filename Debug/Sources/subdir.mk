################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
<<<<<<< Upstream, based on origin/Project_3
../Sources/main.c \
../Sources/nrf24L01.c \
../Sources/spi.c \
../Sources/uart.c 
=======
../Sources/main.c 
>>>>>>> 8d6f30e Integrated all the Project_3 components together

OBJS += \
<<<<<<< Upstream, based on origin/Project_3
./Sources/main.o \
./Sources/nrf24L01.o \
./Sources/spi.o \
./Sources/uart.o 
=======
./Sources/main.o 
>>>>>>> 8d6f30e Integrated all the Project_3 components together

C_DEPS += \
<<<<<<< Upstream, based on origin/Project_3
./Sources/main.d \
./Sources/nrf24L01.d \
./Sources/spi.d \
./Sources/uart.d 
=======
./Sources/main.d 
>>>>>>> 8d6f30e Integrated all the Project_3 components together


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


