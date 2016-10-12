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

#define FRAM_Power_Up_Counter_ADRRESS 0xD000
const uint16_t zero_16 = 0;

/*
 * main.c
 */

// function prototypes
void ExecuteStateMachine(void);

// global variables
uint8_t FINISHED = 0;
const uint16_t maxMotorVal = 2600;


// declare resonant period variables
uint32_t cantResonantPeriod1;							// averaged resonant period cantilever 1
uint32_t cantResonantPeriod2;							// averaged resonant period cantilever 2
uint32_t cantResonantPeriod3;							// averaged resonant period cantilever 3
uint32_t cantResonantPeriod4;							// averaged resonant period cantilever 4
uint32_t cantResonantPeriod5;							// averaged resonant period cantilever 5

unsigned int* powerUpPtr;


enum PolySci_States {
	Start,
	Initialize,
	Collect_Data,
	Process_Data,
	Collect_Raw_Waveform,
	Send_Data_To_Hub,
} PolySci_State;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;							// Stop watchdog timer
	
    PM5CTL0 &= ~LOCKLPM5;								// unlock I/O's-

    PolySci_State = Start;								// begin state machine in start mode

    while ((!FINISHED == 1))
    {
    	ExecuteStateMachine();							// run the state machine
    }

    // initialzie motor
    init_Hbridge();									// initialize H-Bridge pins
    setMotorDirection(FORWARD);

    setMotorAmplitude(maxMotorVal);					// drive the motor at DC voltage

    while (1)
    {

    }
	return 0;
}

void ExecuteStateMachine(void)
{
  	switch (PolySci_State)
  	{
  	case Start:
  		//powerUpPtr = FRAM_Power_Up_Counter_ADRRESS;	// assign pointer into FRAM
  		//*powerUpPtr = 3;
  		//*powerUpPtr++;								// incrament power up integer
  		PolySci_State = Initialize;					   	// go to initialize state
  		break;

  	case Initialize:
  		initialize__Clocks_MPS430FR5969();				// initialize clock to 8MHz

  		zeroOutFRAMCounters();							// zero out the cantilever data counters

  		init_SPI(HUB);									// initialize SPI settings to hub communiate with hub
  		write_uint8_SPI(0xCC, HUB);						// write handshake byte to hub

  		__delay_cycles(40000000);						// delay for 5 seconds in case of error

  		init_SPI (DAC);									// initialize DAC SPI

  		initCantADC12();								// initialize ADC

  		// intitialize LED
  		P1DIR |= 0x01;									// set P1.0 to output
  		P1SEL0 &= ~0x01;								// select GPIO
  		P1SEL1 &= ~0x01;								// select GPIO
  		P1OUT &= ~0x01;									// default LED to off

  		// initialize capture registers
  		initCaptureRegisters();
  		initCapturePins();
  		initCaptureTimer();

  		//initialize motor
  		init_Hbridge();									// initialize H-Bridge pins
  		setMotorDirection(FORWARD);

  		PolySci_State = Collect_Data;					// move to collect data state
  		break;

  	case Collect_Data:
  		__enable_interrupt();							// enable interrupts

  		uint16_t count = 0;
  		uint16_t spinPolarity = 0;						// variable to determine forward or reverse spin direction on motor

  		// zero out FRAM Data
  		zeroOutFRAMCantileverData1();					// zero out the FRAM Array Cantilver 1
  		zeroOutFRAMCantileverData2();					// zero out the FRAM Array Cantilver 2
  		zeroOutFRAMCantileverData3();					// zero out the FRAM Array Cantilver 3
  		zeroOutFRAMCantileverData4();					// zero out the FRAM Array Cantilver 4
  		zeroOutFRAMCantileverData5();					// zero out the FRAM Array Cantilver 5

  		zeroOutFRAMCounters();							// zero out the cantilever data counters

  		// stop motor
  		setMotorAmplitude(0x0000);					// stop motor
  		motorOpen();								// bring motor to open state as recomended from datasheet
  		__delay_cycles(20);							// let voltage levels settle

  		// collect data from 100 pulses from the motor
  		for (count = 0; count < 10; count++)
  		{
  			resetCantileverPeriodCounters();				// reset period array counters

  			// collect and proccess data for 1 pulse
  			//periodCount = 0;
  			//collectData(maxMotorVal, FORWARD);
  			//periodRes = (edge2 - edge1);
  			//cantData5[cantCounter5] = periodRes;
  			//cantCounter5++;

  			collectData(maxMotorVal, (spinPolarity % 0x0002));

  			// process cantilever data collected for pulse "i"
  			processPeriodDataCant1();
  			processPeriodDataCant2();
  			processPeriodDataCant3();
  			processPeriodDataCant4();
  			processPeriodDataCant5();

  			//zero out cantilever data processing arrays
  			zeroOutArraysCant1();
  			zeroOutArraysCant2();
  			zeroOutArraysCant3();
  			zeroOutArraysCant4();
  			zeroOutArraysCant5();

  			spinPolarity++;								 // incrament spin direction variable
  		}
  		readFRAMCantileverData();
  		PolySci_State = Process_Data;				     // move to Process Data state
  		break;

  	case Process_Data:

  		cant1MedianFilter(findCant1Median());
  		cantResonantPeriod1 = averageCant1Data();

  		cant2MedianFilter(findCant2Median());
  		cantResonantPeriod2 = averageCant2Data();

  	  	cant3MedianFilter(findCant3Median());
  	  	cantResonantPeriod3 = averageCant3Data();

  	  	cant4MedianFilter(findCant4Median());
  	  	cantResonantPeriod4 = averageCant4Data();

	  	cant5MedianFilter(findCant5Median());
  	  	cantResonantPeriod5 = averageCant5Data();

 		// on the 18th power up cycle
  		//if ((*powerUpPtr) >= 18)
  		//{
  		//	P1OUT |= 0x01;								// turn LED on
  		//	Get_Raw_Data = 1;							// get raw data from ADC
  		//	PolySci_State = Collect_Raw_Waveform;		// move to collect raw waveform state
  		//}


  		PolySci_State = Send_Data_To_Hub;		   // move to Process Data state


  	//	PolySci_State = Collect_Raw_Waveform;
  		break;

  	case Collect_Raw_Waveform:
  		__enable_interrupt();							// enable interrupts
  		collectRawWaveformData(maxMotorVal, FORWARD);	// collect raw data
  		powerUpCounter = 0;							   	// reset power up count
  		PolySci_State = Send_Data_To_Hub;			  	// move to Process Data state
  		break;

  	case Send_Data_To_Hub:

  		init_SPI(HUB);
  		P1OUT |= HUB_CS;								// Pulls SYNC high

  		uint16_t packetCount;

  		for (packetCount = 0; packetCount < 20; packetCount++)
  		{
  			write_uint32_SPI(cantResonantPeriod1, HUB);
  			write_uint32_SPI(cantResonantPeriod2, HUB);
  			write_uint32_SPI(cantResonantPeriod3, HUB);
  			write_uint32_SPI(cantResonantPeriod4, HUB);
  			write_uint32_SPI(cantResonantPeriod5, HUB);
  		}

  		P1OUT &= ~HUB_CS;								// Pulls SYNC low

  		// zero out FRAM Data
  		zeroOutFRAMCantileverData1();					// zero out the FRAM Array Cantilver 1
  		zeroOutFRAMCantileverData2();					// zero out the FRAM Array Cantilver 2
  		zeroOutFRAMCantileverData3();					// zero out the FRAM Array Cantilver 3
  		zeroOutFRAMCantileverData4();					// zero out the FRAM Array Cantilver 4
  		zeroOutFRAMCantileverData5();					// zero out the FRAM Array Cantilver 5

  		zeroOutFRAMCounters();							// zero out the cantilever data counters

  		FINISHED = 1;									// finish state machine
  		break;

  	default:
  		PolySci_State = Start;

  	}
}
