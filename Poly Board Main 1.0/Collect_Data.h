/*
 * Collect_Data.h
 *
 *  Created on: Sep 29, 2016
 *      Author: CNogales
 */

#ifndef COLLECT_DATA_H_
#define COLLECT_DATA_H_

void collectData(uint16_t, uint8_t);

void zeroOutArraysCant1(void);
void zeroOutArraysCant2(void);
void zeroOutArraysCant3(void);
void zeroOutArraysCant4(void);
void zeroOutArraysCant5(void);

void zeroOutFRAMCantileverData1(void);
void zeroOutFRAMCantileverData2(void);
void zeroOutFRAMCantileverData3(void);
void zeroOutFRAMCantileverData4(void);
void zeroOutFRAMCantileverData5(void);

void zeroOutFRAMCounters(void);

void readFRAMCantileverData(void);

// initialize cantilever timer data arrays
uint32_t timerDataCant1[30];
uint32_t timerDataCant2[30];
uint32_t timerDataCant3[30];
uint32_t timerDataCant4[30];
uint32_t timerDataCant5[30];

// initialize cantilever period data arrays
uint32_t periodDataCant1[30];
uint32_t periodDataCant2[30];
uint32_t periodDataCant3[30];
uint32_t periodDataCant4[30];
uint32_t periodDataCant5[30];

// initialize cantilever delta period data arrays
int32_t deltaPeriodCant1[30];
int32_t deltaPeriodCant2[30];
int32_t deltaPeriodCant3[30];
int32_t deltaPeriodCant4[30];
int32_t deltaPeriodCant5[30];

// initialize cantilever filtered period data arrays
uint32_t filteredDataCant1[30];
uint32_t filteredDataCant2[30];
uint32_t filteredDataCant3[30];
uint32_t filteredDataCant4[30];
uint32_t filteredDataCant5[30];

uint8_t i;

static uint8_t Get_Raw_Data = 0;							// variable to determine if raw data should be collected

//uint32_t timerData[50];
//uint32_t periodData[50];
//int32_t deltaPeriod[50];
//int32_t filteredData[10];
//uint32_t dataArr[100];



#endif /* COLLECT_DATA_H_ */
