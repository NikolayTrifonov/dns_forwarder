################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/DnsHeader.cpp \
../src/net/EndPoint.cpp \
../src/net/NetComponent.cpp 

OBJS += \
./src/net/DnsHeader.o \
./src/net/EndPoint.o \
./src/net/NetComponent.o 

CPP_DEPS += \
./src/net/DnsHeader.d \
./src/net/EndPoint.d \
./src/net/NetComponent.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/%.o: ../src/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


