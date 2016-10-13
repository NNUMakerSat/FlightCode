/*
 * Process_Data.h
 *
 *  Created on: Oct 8, 2016
 *      Author: CNogales
 */

#ifndef PROCESS_DATA_H_
#define PROCESS_DATA_H_

void processPeriodDataCant1(void);
void processPeriodDataCant2(void);
void processPeriodDataCant3(void);
void processPeriodDataCant4(void);
void processPeriodDataCant5(void);

uint32_t findCant1Median(void);
uint32_t findCant2Median(void);
uint32_t findCant3Median(void);
uint32_t findCant4Median(void);
uint32_t findCant5Median(void);

uint32_t averageCant1Data(void);
uint32_t averageCant2Data(void);
uint32_t averageCant3Data(void);
uint32_t averageCant4Data(void);
uint32_t averageCant5Data(void);

void cant1MedianFilter(uint32_t median);
void cant2MedianFilter(uint32_t median);
void cant3MedianFilter(uint32_t median);
void cant4MedianFilter(uint32_t median);
void cant5MedianFilter(uint32_t median);

#endif /* PROCESS_DATA_H_ */
