################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/udpServer/UdpServer.cpp 

OBJS += \
./src/udpServer/UdpServer.o 

CPP_DEPS += \
./src/udpServer/UdpServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/udpServer/%.o: ../src/udpServer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


