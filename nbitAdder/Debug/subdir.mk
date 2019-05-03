################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fulladder.cpp \
../halfadder.cpp \
../nBitAdder.cpp \
../nBitAdder_tb.cpp \
../oder.cpp 

OBJS += \
./fulladder.o \
./halfadder.o \
./nBitAdder.o \
./nBitAdder_tb.o \
./oder.o 

CPP_DEPS += \
./fulladder.d \
./halfadder.d \
./nBitAdder.d \
./nBitAdder_tb.d \
./oder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.2/include -O0 -g3 -Wall -c -fmessage-length=0 -fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


