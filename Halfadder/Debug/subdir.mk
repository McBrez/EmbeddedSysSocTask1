################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../adder_tb.cpp \
../fulladder.cpp \
../halfadder.cpp \
../oder.cpp 

OBJS += \
./adder_tb.o \
./fulladder.o \
./halfadder.o \
./oder.o 

CPP_DEPS += \
./adder_tb.d \
./fulladder.d \
./halfadder.d \
./oder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.2/include -O0 -g3 -Wall -c -fmessage-length=0-fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


