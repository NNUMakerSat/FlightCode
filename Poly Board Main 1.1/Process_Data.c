/*
 * Process_Data.c
 *
 *  Created on: Oct 8, 2016
 *      Author: CNogales
 */
#include <msp430.h>
#include <stdint.h>
#include "Motor_Control.h"
#include "Initialize.h"
#include "SPI_Polling.h"
#include "Freq_Capture.h"
#include <stdbool.h>
#include "FRAM_Write.h"
#include "Collect_Data.h"
#include "Process_Data.h"

void processPeriodDataCant1(void)
{
	// calculate period of output from rising edge incraments
	for (i = 0; i < 30; i++)
	{
		periodDataCant1[i] = (timerDataCant1[i] - timerDataCant1[i - 1]);
	}

	// calculate the change in period
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant1[i] = (periodDataCant1[i] - periodDataCant1[i - 1]);
	}

	// filter out bad data
	for (i = 0; i < 30; i++)
	{
		if (deltaPeriodCant1[i] < 500 && deltaPeriodCant1[i] > -500)
		{
			filteredDataCant1[i] = periodDataCant1[i - 1];
		}

	}

	// store data in master array in FRAM
	for (i = 0; i < 30; i++)
	{
		if (filteredDataCant1[i] > 0x00000000)
		{
			cantData1[cantCounter1] = filteredDataCant1[i];
			cantCounter1++;
		}
	}
}

void processPeriodDataCant2(void)
{
	// calculate period of output from rising edge incraments
	for (i = 0; i < 30; i++)
	{
		periodDataCant2[i] = (timerDataCant2[i] - timerDataCant2[i - 1]);
	}

	// calculate the change in period
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant2[i] = (periodDataCant2[i] - periodDataCant2[i - 1]);
	}

	// filter out bad data
	for (i = 0; i < 30; i++)
	{
		if (deltaPeriodCant2[i] < 500 && deltaPeriodCant2[i] > -500)
		{
			filteredDataCant2[i] = periodDataCant2[i - 1];
		}

	}

	// store data in master array in FRAM
	for (i = 0; i < 30; i++)
	{
		if (filteredDataCant2[i] > 0x00000000)
		{
			cantData2[cantCounter2] = filteredDataCant2[i];
			cantCounter2++;
		}
	}
}

void processPeriodDataCant3(void)
{
	// calculate period of output from rising edge incraments
	for (i = 0; i < 30; i++)
	{
		periodDataCant3[i] = (timerDataCant3[i] - timerDataCant3[i - 1]);
	}

	// calculate the change in period
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant3[i] = (periodDataCant3[i] - periodDataCant3[i - 1]);
	}

	// filter out bad data
	for (i = 0; i < 30; i++)
	{
		if (deltaPeriodCant3[i] < 500 && deltaPeriodCant3[i] > -500)
		{
			filteredDataCant3[i] = periodDataCant3[i - 1];
		}

	}

	// store data in master array in FRAM
	for (i = 0; i < 30; i++)
	{
		if (filteredDataCant3[i] > 0x00000000)
		{
			cantData3[cantCounter3] = filteredDataCant3[i];
			cantCounter3++;
		}
	}
}

void processPeriodDataCant4(void)
{
	// calculate period of output from rising edge incraments
	for (i = 0; i < 30; i++)
	{
		periodDataCant4[i] = (timerDataCant4[i] - timerDataCant4[i - 1]);
	}

	// calculate the change in period
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant4[i] = (periodDataCant4[i] - periodDataCant4[i - 1]);
	}

	// filter out bad data
	for (i = 0; i < 30; i++)
	{
		if (deltaPeriodCant4[i] < 500 && deltaPeriodCant4[i] > -500)
		{
			filteredDataCant4[i] = periodDataCant4[i - 1];
		}

	}

	// store data in master array in FRAM
	for (i = 0; i < 30; i++)
	{
		if (filteredDataCant4[i] > 0x00000000)
		{
			cantData4[cantCounter4] = filteredDataCant4[i];
			cantCounter4++;
		}
	}
}

void processPeriodDataCant5(void)
{
	// calculate period of output from rising edge incraments
	for (i = 0; i < 30; i++)
	{
		periodDataCant5[i] = (timerDataCant5[i] - timerDataCant5[i - 1]);
	}

	// calculate the change in period
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant5[i] = (periodDataCant5[i] - periodDataCant5[i - 1]);
	}

	// filter out bad data
	for (i = 0; i < 30; i++)
	{
		if (deltaPeriodCant5[i] < 500 && deltaPeriodCant5[i] > -500)
		{
			filteredDataCant5[i] = periodDataCant5[i - 1];
		}

	}

	// store data in master array in FRAM
	for (i = 0; i < 30; i++)
	{
		if (filteredDataCant5[i] > 0x00000000)
		{
			cantData5[cantCounter5] = filteredDataCant5[i];
			cantCounter5++;
		}
	}
}




uint32_t findCant1Median(void)
{
	//////////////////////////////////// Bubble Sort //////////////////////////////////////////////////////

	uint32_t medianVal;															// median value

	uint8_t swap = 0;					// variable to tell if swap needs to take place
	uint32_t temp = 0;					// variable to swap data

	do
	{
		swap = 0;
		uint8_t bubbleCount = 0;

		for (bubbleCount = 0; bubbleCount < (cantCounter1 - 1); bubbleCount++)
		{
			if (cantData1[bubbleCount] > cantData1[bubbleCount + 1])
			{
				temp = cantData1[bubbleCount];
				cantData1[bubbleCount] = cantData1[bubbleCount + 1];
				cantData1[bubbleCount + 1] = temp;
				swap = 1;
			}
		}
	} while (swap);

	medianVal = cantData1[(cantCounter1 / 2)];

	return medianVal;

}

uint32_t findCant2Median(void)
{
	//////////////////////////////////// Bubble Sort //////////////////////////////////////////////////////

	uint32_t medianVal;															// median value

	uint8_t swap = 0;					// variable to tell if swap needs to take place
	uint32_t temp = 0;					// variable to swap data

	do
	{
		swap = 0;
		uint8_t bubbleCount = 0;

		for (bubbleCount = 0; bubbleCount < (cantCounter2 - 1); bubbleCount++)
		{
			if (cantData2[bubbleCount] > cantData2[bubbleCount + 1])
			{
				temp = cantData2[bubbleCount];
				cantData2[bubbleCount] = cantData2[bubbleCount + 1];
				cantData2[bubbleCount + 1] = temp;
				swap = 1;
			}
		}
	} while (swap);

	medianVal = cantData2[(cantCounter2 / 2)];

	return medianVal;

}

uint32_t findCant3Median(void)
{
	//////////////////////////////////// Bubble Sort //////////////////////////////////////////////////////

	uint32_t medianVal;															// median value

	uint8_t swap = 0;					// variable to tell if swap needs to take place
	uint32_t temp = 0;					// variable to swap data

	do
	{
		swap = 0;
		uint8_t bubbleCount = 0;

		for (bubbleCount = 0; bubbleCount < (cantCounter3 - 1); bubbleCount++)
		{
			if (cantData3[bubbleCount] > cantData3[bubbleCount + 1])
			{
				temp = cantData3[bubbleCount];
				cantData3[bubbleCount] = cantData3[bubbleCount + 1];
				cantData3[bubbleCount + 1] = temp;
				swap = 1;
			}
		}
	} while (swap);

	medianVal = cantData3[(cantCounter3 / 2)];

	return medianVal;

}

uint32_t findCant4Median(void)
{
	//////////////////////////////////// Bubble Sort //////////////////////////////////////////////////////

	uint32_t medianVal;															// median value

	uint8_t swap = 0;					// variable to tell if swap needs to take place
	uint32_t temp = 0;					// variable to swap data

	do
	{
		swap = 0;
		uint8_t bubbleCount = 0;

		for (bubbleCount = 0; bubbleCount < (cantCounter4 - 1); bubbleCount++)
		{
			if (cantData4[bubbleCount] > cantData4[bubbleCount + 1])
			{
				temp = cantData4[bubbleCount];
				cantData4[bubbleCount] = cantData4[bubbleCount + 1];
				cantData4[bubbleCount + 1] = temp;
				swap = 1;
			}
		}
	} while (swap);

	medianVal = cantData4[(cantCounter4 / 2)];

	return medianVal;

}

uint32_t findCant5Median(void)
{
	//////////////////////////////////// Bubble Sort //////////////////////////////////////////////////////

	uint32_t medianVal;															// median value

	uint8_t swap = 0;					// variable to tell if swap needs to take place
	uint32_t temp = 0;					// variable to swap data

	do
	{
		swap = 0;
		uint8_t bubbleCount = 0;

		for (bubbleCount = 0; bubbleCount < (cantCounter5 - 1); bubbleCount++)
		{
			if (cantData5[bubbleCount] > cantData5[bubbleCount + 1])
			{
				temp = cantData5[bubbleCount];
				cantData5[bubbleCount] = cantData5[bubbleCount + 1];
				cantData5[bubbleCount + 1] = temp;
				swap = 1;
			}
		}
	} while (swap);

	medianVal = cantData5[(cantCounter5 / 2)];

	return medianVal;

}

void cant1MedianFilter(uint32_t median)
{
	for (i = 0; i < cantCounter1; i++)
	{
		// if the data point is not within + or - 5000 of median then through out the data point
		if (cantData1[i] > (median + 5000) && cantData1[i] < (median - 5000))
		{
			cantData1[i] = 0;					// get rid of value
		}
	}
}

void cant2MedianFilter(uint32_t median)
{
	for (i = 0; i < cantCounter2; i++)
	{
		// if the data point is not within + or - 10000 of median then through out the data point
		if (cantData2[i] > (median + 5000) && cantData2[i] < (median - 5000))
		{
			cantData2[i] = 0;					// get rid of value
		}
	}
}

void cant3MedianFilter(uint32_t median)
{
	for (i = 0; i < cantCounter3; i++)
	{
		// if the data point is not within + or - 10000 of median then through out the data point
		if (cantData3[i] > (median + 5000) && cantData3[i] < (median - 5000))
		{
			cantData3[i] = 0;					// get rid of value
		}
	}
}

void cant4MedianFilter(uint32_t median)
{
	for (i = 0; i < cantCounter4; i++)
	{
		// if the data point is not within + or - 10000 of median then through out the data point
		if (cantData4[i] > (median + 5000) && cantData4[i] < (median - 5000))
		{
			cantData4[i] = 0;					// get rid of value
		}
	}
}

void cant5MedianFilter(uint32_t median)
{
	for (i = 0; i < cantCounter5; i++)
	{
		// if the data point is not within + or - 10000 of median then through out the data point
		if (cantData5[i] > (median + 5000) && cantData5[i] < (median - 5000))
		{
			cantData5[i] = 0;					// get rid of value
		}
	}
}

uint32_t averageCant1Data(void)
{
	uint32_t sum = 0;							// sum of period values
	uint32_t average = 0;						// average of period values

	for (i = 0; i < cantCounter1; i++)
	{
		sum = (sum + cantData1[i]);
	}

	average = (sum / cantCounter1);

	return average;
}

uint32_t averageCant2Data(void)
{
	uint32_t sum = 0;							// sum of period values
	uint32_t average = 0;						// average of period values

	for (i = 0; i < cantCounter2; i++)
	{
		sum = (sum + cantData2[i]);
	}

	average = (sum / cantCounter2);

	return average;
}

uint32_t averageCant3Data(void)
{
	uint32_t sum = 0;							// sum of period values
	uint32_t average = 0;						// average of period values

	for (i = 0; i < cantCounter3; i++)
	{
		sum = (sum + cantData3[i]);
	}

	average = (sum / cantCounter3);

	return average;
}

uint32_t averageCant4Data(void)
{
	uint32_t sum = 0;							// sum of period values
	uint32_t average = 0;						// average of period values

	for (i = 0; i < cantCounter4; i++)
	{
		sum = (sum + cantData4[i]);
	}

	average = (sum / cantCounter4);

	return average;
}

uint32_t averageCant5Data(void)
{
	uint32_t sum = 0;							// sum of period values
	uint32_t average = 0;						// average of period values

	for (i = 0; i < cantCounter5; i++)
	{
		sum = (sum + cantData5[i]);
	}

	average = (sum / cantCounter5);

	return average;
}



