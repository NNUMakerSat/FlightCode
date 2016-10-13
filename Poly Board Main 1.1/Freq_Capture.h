/*
 * Freq_Capture.h
 *
 *  Created on: Sep 19, 2016
 *      Author: CNogales
 */

#include <msp430.h>
#include <stdint.h>

#ifndef FREQ_CAPTURE_H_
#define FREQ_CAPTURE_H_

#define CCI1A 0x10				// P1.4
#define CCI2A 0x20				// P1.5
#define CCI3A 0x10				// P3.4
#define CCI4A 0x20				// P3.5
#define CCI5A 0x40				// P3.6

#define refCantADC 0x10			// 2.4
#define cant5ADC 0x08			// 4.3

void initCaptureTimer(void);
void initCaptureRegisters(void);
void initCapturePins(void);
void collectRawWaveformData(uint16_t, uint8_t);
void resetCantileverPeriodCounters(void);
void startTimer(void);
void stopTimer(void);

void initCantADC12(void);
void initialize_ADC12(void);
void startADC12(void);
void stopADC12(void);
void ADC12SampleHoldTimeTo_512_clk_cycles(void);
void ADC12SampleHoldTimeTo_4_clk_cycles(void);




uint16_t rawRefCantWave[200];
uint16_t rawCant5Wave[200];
uint16_t rawRefCantCounter;
uint16_t rawCant5Counter;

static uint32_t offset;
static uint32_t cant1;
static uint32_t cant2;
static uint32_t cant3;
static uint32_t cant4;
static uint32_t cant5;
static uint8_t bufferCounter = 0;

uint8_t periodCount;
uint32_t edge1;
uint32_t edge2;
uint32_t periodRes;

static uint8_t cantPeriodCount1;
static uint8_t cantPeriodCount2;
static uint8_t cantPeriodCount3;
static uint8_t cantPeriodCount4;
static uint8_t cantPeriodCount5;

#endif /* FREQ_CAPTURE_H_ */
