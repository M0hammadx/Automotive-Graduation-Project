################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

CMD_SRCS += \
../TM4C123GH6PM.cmd 

C_SRCS += \
../ECU.c \
../System.c \
../UART.c \
../global.c \
../main.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./ECU.d \
./System.d \
./UART.d \
./global.d \
./main.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./ECU.obj \
./System.obj \
./UART.obj \
./global.obj \
./main.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"ECU.obj" \
"System.obj" \
"UART.obj" \
"global.obj" \
"main.obj" 

C_DEPS__QUOTED += \
"ECU.d" \
"System.d" \
"UART.d" \
"global.d" \
"main.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../ECU.c" \
"../System.c" \
"../UART.c" \
"../global.c" \
"../main.c" 


