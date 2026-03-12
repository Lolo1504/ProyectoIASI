################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AStar.cpp \
../src/BestFirst.cpp \
../src/Heuristica.cpp \
../src/HillClimbing.cpp \
../src/ManejoFicheros.cpp \
../src/Objetivo.cpp \
../src/ProyectoIASI_12_03.cpp \
../src/Sucesores.cpp \
../src/Tablero.cpp 

CPP_DEPS += \
./src/AStar.d \
./src/BestFirst.d \
./src/Heuristica.d \
./src/HillClimbing.d \
./src/ManejoFicheros.d \
./src/Objetivo.d \
./src/ProyectoIASI_12_03.d \
./src/Sucesores.d \
./src/Tablero.d 

OBJS += \
./src/AStar.o \
./src/BestFirst.o \
./src/Heuristica.o \
./src/HillClimbing.o \
./src/ManejoFicheros.o \
./src/Objetivo.o \
./src/ProyectoIASI_12_03.o \
./src/Sucesores.o \
./src/Tablero.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AStar.d ./src/AStar.o ./src/BestFirst.d ./src/BestFirst.o ./src/Heuristica.d ./src/Heuristica.o ./src/HillClimbing.d ./src/HillClimbing.o ./src/ManejoFicheros.d ./src/ManejoFicheros.o ./src/Objetivo.d ./src/Objetivo.o ./src/ProyectoIASI_12_03.d ./src/ProyectoIASI_12_03.o ./src/Sucesores.d ./src/Sucesores.o ./src/Tablero.d ./src/Tablero.o

.PHONY: clean-src

