/*
 * FRAM_Write.h
 *
 *  Created on: Sep 29, 2016
 *      Author: CNogales
 */

#include <stdint.h>

#ifndef FRAM_WRITE_H_
#define FRAM_WRITE_H_

// allocate cantilever 1 data array
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(cantData1)
static uint32_t cantData1[1000] = {0};
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned long cantData1[1000] = {0};
#else
#error Compiler not supported!
#endif

// allocate cantilever 2 data array
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(cantData2)
static uint32_t cantData2[1000] = {0};
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned long cantData2[1000] = {0};
#else
#error Compiler not supported!
#endif

// allocate cantilever 3 data array
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(cantData3)
static uint32_t cantData3[1000] = {0};
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned long cantData3[1000] = {0};
#else
#error Compiler not supported!
#endif

// allocate cantilever 4 data array
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(cantData4)
static uint32_t cantData4[1000] = {0};
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned long cantData4[1000] = {0};
#else
#error Compiler not supported!
#endif

// allocate cantilever 5 data array
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(cantData5)
static uint32_t cantData5[1000] = {0};
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned long cantData5[1000] = {0};
#else
#error Compiler not supported!
#endif

// create counter to count the number of power ups and determine whether to collect raw data on waveform
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(powerUpCounter)
static unsigned int powerUpCounter;
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent unsigned int powerUpCounter;
#else
#error Compiler not supported!
#endif


static uint8_t cantCounter1;
static uint8_t cantCounter2;
static uint8_t cantCounter3;
static uint8_t cantCounter4;
static uint8_t cantCounter5;

uint32_t* cant1FRAMPtr;
uint32_t* cant2FRAMPtr;
uint32_t* cant3FRAMPtr;
uint32_t* cant4FRAMPtr;
uint32_t* cant5FRAMPtr;


#endif /* FRAM_WRITE_H_ */
