/*
 * Collect_Data.c
 *
 *  Created on: Sep 29, 2016
 *      Author: CNogales
 */

#include <msp430.h>
#include <stdint.h>
#include "Collect_Data.h"
#include "Motor_Control.h"
#include "Freq_Capture.h"
#include "FRAM_Write.h"


void collectData(uint16_t motorVal, uint8_t polarity)
{
	uint16_t zero = 0;							// 16 bit zero
	setMotorDirection(polarity);				// set motor to forward or reverse
	setMotorAmplitude(motorVal);				// drive the motor at DC voltage
	__delay_cycles(2000000);					// .25 second delay
	startADC12();							   // begin sampling the ADC again
	setMotorAmplitude(zero);					// stop motor
	motorOpen();								// bring motor to open state as recomended from datasheet
	__delay_cycles(20);							// let voltage levels settle
	motorBrake();								// break motor
	while(ADC12MEM2 > 100){}					// while the motor voltage is not zero
	stopADC12();								// halt ADC sampling
	offset = 0;									// set offset back to zero
	TB0R = 0x00;								// reset timer
	startTimer();								// begin collecting data
	__delay_cycles(800000);						// delay 0.1s to collect data
	stopTimer();								// stop timer

	return;
}

void collectRawWaveformData(uint16_t motorVal, uint8_t polarity)
{
	uint16_t zero = 0;							// 16 bit zero
	setMotorDirection(polarity);				// set motor to forward or reverse
	setMotorAmplitude(motorVal);				// drive the motor at DC voltage
	__delay_cycles(2000000);					// .25 second delay
	setMotorAmplitude(zero);					// stop motor
	motorOpen();								// bring motor to open state as recomended from datasheet
	__delay_cycles(20);							// let voltage levels settle
	motorBrake();								// break motor
	startADC12();
	while(rawRefCantCounter < 200){};			// fill up array with data
	stopADC12();

}



void zeroOutArraysCant1(void)
{
	// zero out timer array
	for (i = 0; i < 30; i++)
	{
		timerDataCant1[i] = 0;
	}

	// zero out period array
	for (i = 0; i < 30; i++)
	{
		periodDataCant1[i] = 0;
	}

	// zero out deltaPeriod array
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant1[i] = 0;
	}

	// zero out filteredData array
	for (i = 0; i < 30; i++)
	{
		filteredDataCant1[i] = 0;
	}

}

void zeroOutArraysCant2(void)
{
	// zero out timer array
	for (i = 0; i < 30; i++)
	{
		timerDataCant2[i] = 0;
	}

	// zero out period array
	for (i = 0; i < 30; i++)
	{
		periodDataCant2[i] = 0;
	}

	// zero out deltaPeriod array
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant2[i] = 0;
	}

	// zero out filteredData array
	for (i = 0; i < 30; i++)
	{
		filteredDataCant2[i] = 0;
	}

}

void zeroOutArraysCant3(void)
{
	// zero out timer array
	for (i = 0; i < 30; i++)
	{
		timerDataCant3[i] = 0;
	}

	// zero out period array
	for (i = 0; i < 30; i++)
	{
		periodDataCant3[i] = 0;
	}

	// zero out deltaPeriod array
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant3[i] = 0;
	}

	// zero out filteredData array
	for (i = 0; i < 30; i++)
	{
		filteredDataCant3[i] = 0;
	}

}

void zeroOutArraysCant4(void)
{
	// zero out timer array
	for (i = 0; i < 30; i++)
	{
		timerDataCant4[i] = 0;
	}

	// zero out period array
	for (i = 0; i < 30; i++)
	{
		periodDataCant4[i] = 0;
	}

	// zero out deltaPeriod array
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant4[i] = 0;
	}

	// zero out filteredData array
	for (i = 0; i < 30; i++)
	{
		filteredDataCant4[i] = 0;
	}

}

void zeroOutArraysCant5(void)
{
	// zero out timer array
	for (i = 0; i < 30; i++)
	{
		timerDataCant5[i] = 0;
	}

	// zero out period array
	for (i = 0; i < 30; i++)
	{
		periodDataCant5[i] = 0;
	}

	// zero out deltaPeriod array
	for (i = 0; i < 30; i++)
	{
		deltaPeriodCant5[i] = 0;
	}

	// zero out filteredData array
	for (i = 0; i < 30; i++)
	{
		filteredDataCant5[i] = 0;
	}

}

void readFRAMCantileverData(void)
{
	// read cantData5 array
	for (i = 0; i < 100; i++)
	{
		//dataArr[i] = cantData5[i];
	}
}



void zeroOutFRAMCantileverData1(void)
{
	uint16_t z;
	for (z = cantCounter1; z < cantCounter1; z++)
	{
		cantData1[z] = 0;
	}
}

void zeroOutFRAMCantileverData2(void)
{
	uint16_t z;
	for (z = cantCounter2; z < cantCounter2; z++)
	{
		cantData2[z] = 0;
	}
}

void zeroOutFRAMCantileverData3(void)
{
	uint16_t z;
	for (z = cantCounter3; z < cantCounter3; z++)
	{
		cantData3[z] = 0;
	}
}

void zeroOutFRAMCantileverData4(void)
{
	uint16_t z;
	for (z = cantCounter4; z < cantCounter4; z++)
	{
		cantData4[z] = 0;
	}
}

void zeroOutFRAMCantileverData5(void)
{
	uint16_t z;
	for (z = cantCounter5; z < cantCounter5; z++)
	{
		cantData5[z] = 0;
	}
}

void zeroOutFRAMCounters(void)
{
	cantCounter1 = 0x0000;
	cantCounter2 = 0x0000;
	cantCounter3 = 0x0000;
	cantCounter4 = 0x0000;
	cantCounter5 = 0x0000;
}

	//return 0;

