################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dnsForwarder/DnsForwarder.cpp 

OBJS += \
./src/dnsForwarder/DnsForwarder.o 

CPP_DEPS += \
./src/dnsForwarder/DnsForwarder.d 


# Each subdirectory must supply rules for building sources it contributes
src/dnsForwarder/%.o: ../src/dnsForwarder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=gnu++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


