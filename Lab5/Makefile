#******************************************************************************
#
# Makefile - Rules for building the FreeRTOS example.
#
# Copyright (c) 2012-2014 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.0.12573 of the EK-TM4C123GXL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=../../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../../../third_party/FreeRTOS/Source/portable/GCC/ARM_CM4F
VPATH+=../../../third_party/FreeRTOS/Source/portable/MemMang/
VPATH+=../../../third_party/FreeRTOS/Source
VPATH+=../drivers
VPATH+=../../../utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=..
IPATH+=../../..
IPATH+=../../../third_party/FreeRTOS/Source/portable/GCC/ARM_CM4F
IPATH+=../../../third_party/FreeRTOS
IPATH+=../../../third_party/FreeRTOS/Source/include
IPATH+=../../../third_party

#
# The default rule, which causes the FreeRTOS example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/main.axf


debug: CFLAGS+= -g -D DEBUG
debug: ${COMPILER}
debug: ${COMPILER}/main.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the FreeRTOS example.
#
${COMPILER}/main.axf: ${COMPILER}/main.o
${COMPILER}/main.axf: ${COMPILER}/heap_2.o
${COMPILER}/main.axf: ${COMPILER}/list.o
${COMPILER}/main.axf: ${COMPILER}/port.o
${COMPILER}/main.axf: ${COMPILER}/queue.o
${COMPILER}/main.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/main.axf: ${COMPILER}/tasks.o
${COMPILER}/main.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/main.axf: main.ld
SCATTERgcc_main=main.ld
ENTRY_main=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
