################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tokenizer.o 

C_SRCS += \
../indexer.c \
../sorted-list.c \
../tester.c \
../tokenizer.c 

OBJS += \
./indexer.o \
./sorted-list.o \
./tester.o \
./tokenizer.o 

C_DEPS += \
./indexer.d \
./sorted-list.d \
./tester.d \
./tokenizer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


