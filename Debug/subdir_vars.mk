################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432E401Y_NoRTOS.cmd 

SYSCFG_SRCS += \
../gpiointerrupt.syscfg 

C_SRCS += \
../gpiointerrupt.c \
./syscfg/ti_drivers_config.c \
../main_nortos.c \
../system_msp432e401y.c \
../uartstdio.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./gpiointerrupt.d \
./syscfg/ti_drivers_config.d \
./main_nortos.d \
./system_msp432e401y.d \
./uartstdio.d 

OBJS += \
./gpiointerrupt.obj \
./syscfg/ti_drivers_config.obj \
./main_nortos.obj \
./system_msp432e401y.obj \
./uartstdio.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.exp \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"gpiointerrupt.obj" \
"syscfg\ti_drivers_config.obj" \
"main_nortos.obj" \
"system_msp432e401y.obj" \
"uartstdio.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\ti_utils_build_linker.cmd.exp" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"gpiointerrupt.d" \
"syscfg\ti_drivers_config.d" \
"main_nortos.d" \
"system_msp432e401y.d" \
"uartstdio.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../gpiointerrupt.c" \
"./syscfg/ti_drivers_config.c" \
"../main_nortos.c" \
"../system_msp432e401y.c" \
"../uartstdio.c" 

SYSCFG_SRCS__QUOTED += \
"../gpiointerrupt.syscfg" 


