/*
 * Freq_Capture.c
 *
 *  Created on: Sep 19, 2016
 *      Author: CNogales
 */

#include <msp430.h>
#include <stdint.h>
#include "Freq_Capture.h"
#include "Collect_Data.h"

#define Motor_ADC_1 0x08				// motor_ADC_1 P1.3
#define Motor_ADC_2 0x01				// motor_ADC_2 P3.0
void initCaptureTimer(void)
{
	TB0R = 0X0000;											   	// set timer value to 0
	TB0CTL |= TBSSEL_2 | ID_3 | MC_0 | TBIE;					// SMCLK | /8 | stop timer | enable inturrupt on timer
}

void startTimer(void)
{
	TB0CTL |= MC_2;											// start timer
}

void stopTimer(void)
{
	TB0CTL &= ~MC_2;											// stop timer
}
void initCaptureRegisters(void)
{
	// configure P1.4, CCI1A
	TB0CCTL1 |= CM_1 | CCIS_0 | CAP | CCIE | SCS; 			// capture on rising edge | CCI0A | Capture mode | enable capture/compare interrrupt | synchronus mode
	TB0CCTL1 &= ~CCIFG;										// clear inturrput bit

	// configure P1.5, CCI2A
	TB0CCTL2 |= CM_1 | CCIS_0 | CAP | CCIE | SCS; 			// capture on rising edge | CCI0A | Capture mode | enable capture/compare interrrupt | synchronus mode
	TB0CCTL2 &= ~CCIFG;										// clear inturrput bit

	// configure P3.4, CCI3A
	TB0CCTL3 |= CM_1 | CCIS_0 | CAP | CCIE | SCS; 			// capture on rising edge | CCI0A | Capture mode | enable capture/compare interrrupt | synchronus mode
	TB0CCTL3 &= ~CCIFG;										// clear inturrput bit

	// configure P3.5, CCI4A
	TB0CCTL4 |= CM_1 | CCIS_0 | CAP | CCIE | SCS; 			// capture on rising edge | CCI0A | Capture mode | enable capture/compare interrrupt | synchronus mode
	TB0CCTL4 &= ~CCIFG;										// clear inturrput bit

	// configure P3.6, CCI5A
	TB0CCTL5 |= CM_1 | CCIS_0 | CAP | CCIE | SCS; 			// capture on rising edge | CCI0A | Capture mode | enable capture/compare interrrupt | synchronus mode
	TB0CCTL5 &= ~CCIFG;										// clear inturrput bit
}

void initCapturePins(void)
{
	// select tertiary imput mode P1.4
	P1SEL0 |= CCI1A;
	P1SEL1 &= ~CCI1A;
	P1OUT &= ~CCI1A;

	// select tertiary imput mode P1.5
	P1SEL0 |= CCI2A;
	P1SEL1 &= ~CCI2A;
	P1OUT &= ~CCI2A;

	// select tertiary imput mode P3.4
	P3SEL0 |= CCI3A;
	P3SEL1 &= ~CCI3A;
	P3OUT &= ~CCI3A;

	// select tertiary imput mode P3.5
	P3SEL0 |= CCI4A;
	P3SEL1 &= ~CCI4A;
	P3OUT &= ~CCI4A;

	// select tertiary imput mode P3.6
	P3SEL0 |= CCI5A;
	P3SEL1 &= ~CCI5A;
	P3OUT &= ~CCI5A;
}

void initialize_ADC12(void)
{
	ADC12CTL0 &= ~ADC12ENC;                                    // disable the ADC enable bit

	P1DIR &= ~Motor_ADC_1;									// set motor_ADC_1 to input mode
	P3DIR &= ~Motor_ADC_2;									// set motor_ADC_2 to input mode

	// set Motor_ADC_1 to tertiary module function
	P1SEL0 |= Motor_ADC_1;
	P1SEL1 |= Motor_ADC_1;

	// set Motor_ADC_2 to tertiary module function
	P3SEL0 |= Motor_ADC_2;
	P3SEL1 |= Motor_ADC_2;

	ADC12CTL0 |= ADC12SHT0_10 | ADC12ON;                        // 512 clock cycles per sample | turn ADC on

    ADC12CTL1 |= ADC12SSEL_3 | ADC12PDIV_3 | ADC12DIV_7 | ADC12SHP | ADC12CONSEQ_1;  // select SMCLK as clock source | divide by zero | signal sourced from timer | single conversion multiple channels

    ADC12CTL2 |= ADC12RES_2;                                    // set ADC resolution to 12 bit
    ADC12CTL2 &= ~ADC12DF;                                      // set conversion results to be unsigned binary

    ADC12CTL3 = ADC12CSTARTADD_0;  					           // value is in memory register 0 | single conversion single channel

    // P1.3 ADC Setup
    ADC12MCTL0 |= ADC12INCH_3 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
    ADC12MCTL0 &= ~ADC12EOS;

    // P3.0 ADC Setup
    ADC12MCTL1 |= ADC12INCH_12 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
    ADC12MCTL1 |= ADC12EOS;

    ADC12IER0 |= ADC12IE0;                                      // enable interupt on ADC12IFG0 bit
    ADC12IER0 |= ADC12IE1;                                      // enable interupt on ADC12IFG1 bit

    ADC12CTL0 |= ADC12ENC;                                      // enable conversion
   // ADC12IFGR0 &= ~ADC12IFG0;                                   // clear inturrput flag
}

void initCantADC12(void)
{
	ADC12CTL0 &= ~ADC12ENC;                                    // disable the ADC enable bit

	// set ADC lines to input
	P1DIR &= ~Motor_ADC_1;
	P3DIR &= ~Motor_ADC_2;
	P2DIR &= ~refCantADC;
	P4DIR &= ~cant5ADC;

	// set Motor_ADC_1 to tertiary module function
	P1SEL0 |= Motor_ADC_1;
	P1SEL1 |= Motor_ADC_1;

	// set Motor_ADC_2 to tertiary module function
	P3SEL0 |= Motor_ADC_2;
	P3SEL1 |= Motor_ADC_2;

	// set Refrerence Cantilever ADC to tertiary module function
	P2SEL0 |= refCantADC;
	P2SEL1 |= refCantADC;

	// set Cantilever 5 ADC to tertiary module function
	P4SEL0 |= cant5ADC;
	P4SEL1 |= cant5ADC;

	ADC12CTL0 |= ADC12SHT0_0 | ADC12ON | ADC12MSC;            // 192 clock cycles per sample | turn ADC on | automatic sampling after rising edge on SHI

	ADC12CTL1 |= ADC12DIV_7 | ADC12SSEL_3 |ADC12CONSEQ_3 | ADC12SHP;      // select SMCLK as clock source | divide by 8 | multiple conversions multiple channels

	ADC12CTL2 |= ADC12RES_2;                                    // set ADC resolution to 8 bit
	ADC12CTL2 &= ~ADC12DF;                                      // set conversion results to be unsigned binary

	ADC12CTL3 = ADC12CSTARTADD_0;  					           // value is in memory register 0 | single conversion single channel

	// Reference Cantilever ADC Setup
	ADC12MCTL0 |= ADC12INCH_7 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
	ADC12MCTL0 &= ~ADC12EOS;

	// Cantilver 5 ADC Setup
	ADC12MCTL1 |= ADC12INCH_11 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
	ADC12MCTL1 &= ~ADC12EOS;

	//P1.3 ADC Setup
	ADC12MCTL2 |= ADC12INCH_3 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
	ADC12MCTL2 &= ~ADC12EOS;

	// P3.0 ADC Setup
	ADC12MCTL3 |= ADC12INCH_12 | ADC12VRSEL_0;     			   // select input channel to be 9 | select VCC and VSS as V+ and V- | end of series
	ADC12MCTL3 |= ADC12EOS;


	//ADC12IER0 |= ADC12IE0;                                      // enable interupt on ADC12IFG0 bit
	//ADC12IER0 |= ADC12IE1;                                      // enable interupt on ADC12IFG1 bit
	//ADC12IER0 |= ADC12IE2;                                      // enable interupt on ADC12IFG2 bit
	//ADC12IER0 |= ADC12IE3;                                      // enable interupt on ADC12IFG3 bit

	ADC12CTL0 |= ADC12ENC;                                      // enable conversion
	// ADC12IFGR0 &= ~ADC12IFG0;                                   // clear inturrput flag
}

void ADC12SampleHoldTimeTo_4_clk_cycles(void)
{
	ADC12CTL0 = 0x0000;											// clear register
	ADC12CTL0 |= ADC12SHT0_0 | ADC12ON | ADC12MSC;            // 4 clock cycles per sample | turn ADC on | automatic sampling after rising edge on SHI
	//ADC12CTL0 &= ~ADC12SHT0_10
	//ADC12CTL0 |= ADC12SHT0_0									// set to 4 clock cycles per sample
}

void ADC12SampleHoldTimeTo_512_clk_cycles(void)
{
	ADC12CTL0 = 0x0000;											// clear register
	ADC12CTL0 |= ADC12SHT0_10 | ADC12ON | ADC12MSC;            // 512 clock cycles per sample | turn ADC on | automatic sampling after rising edge on SHI
	//ADC12CTL0 |= ADC12SHT0_10					// set to 512 clock cycles per sample
}

void startADC12(void)
{
	ADC12IER0 |= ADC12IE0;                     // enable interupt on ADC12IFG2 bit
	ADC12IER0 |= ADC12IE1;                     // enable interupt on ADC12IFG3 bit
	ADC12IER0 |= ADC12IE2;                     // enable interupt on ADC12IFG2 bit
	ADC12IER0 |= ADC12IE3;                     // enable interupt on ADC12IFG3 bit
	ADC12CTL0 |= ADC12SC;               	   // begin sampling ADC on motor output lines
}

void stopADC12(void)
{
	ADC12IER0 &= ~ADC12IE0;                     // disable interupt on ADC12IFG2 bit
	ADC12IER0 &= ~ADC12IE1;                     // disable interupt on ADC12IFG3 bit
	ADC12IER0 &= ~ADC12IE2;                     // disable interupt on ADC12IFG2 bit
	ADC12IER0 &= ~ADC12IE3;                     // disable interupt on ADC12IFG3 bit
}

void resetCantileverPeriodCounters(void)
{
	// reset cantilever data counters to zero
	cantPeriodCount1 = 0x00;
	cantPeriodCount2 = 0x00;
	cantPeriodCount3 = 0x00;
	cantPeriodCount4 = 0x00;
	cantPeriodCount5 = 0x00;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TB0_ISR(void) {
	switch (__even_in_range(TB0IV, TB0IV_TBIFG))
	{
	case TB0IV_NONE:
		break;               // No interrupt
	case TB0IV_TBCCR1:
		timerDataCant1[cantPeriodCount1] = (TB0CCR1 + offset);			// store rising edge in data array
		cantPeriodCount1++;												// incrament to next element in array
		break;
	case TB0IV_TBCCR2:
		timerDataCant2[cantPeriodCount2] = (TB0CCR2 + offset);			// store rising edge in data array
		cantPeriodCount2++;												// incrament to next element in array
		break;
	case TB0IV_TBCCR3:
		timerDataCant4[cantPeriodCount4] = (TB0CCR3 + offset);			// store rising edge in data array
		cantPeriodCount4++;												// incrament to next element in array
		break;
	case TB0IV_TBCCR4:
		timerDataCant3[cantPeriodCount3] = (TB0CCR4 + offset);			// store rising edge in data array
		cantPeriodCount3++;												// incrament to next element in array
		break;
	case TB0IV_TBCCR5:
	/*
		if (periodCount == 2)
		{
			edge1 = (TB0CCR5 + offset);
		}

		if (periodCount == 3)
		{
			edge2 = (TB0CCR5 + offset);
		}

		periodCount += 1;
	*/
		timerDataCant5[cantPeriodCount5] = (TB0CCR5 + offset);			// store rising edge in data array
		cantPeriodCount5++;												// incrament to next element in array
		break;
	case TB0IV_TBCCR6:
		break;               // CCR6 not used
	case TB0IV_TBIFG:                       // overflow
		offset += 0x10000;
		break;
	default:
		break;
	}
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
	if (Get_Raw_Data == 1)
	{
		rawRefCantWave[rawRefCantCounter] = ADC12MEM0;		// store ref waveform in array
		rawCant5Wave[rawCant5Counter] = ADC12MEM1;			// store cant 5 waveform in array
		rawRefCantCounter++;								// incrament raw ref counter
		rawCant5Counter++;									// incrament raw cant5 counter

		ADC12IFGR0 &= ~ADC12IFG0;                           // clear inturrput flag on ADC12MEM0
		ADC12IFGR0 &= ~ADC12IFG1;                           // clear inturrput flag on ADC12MEM1
		ADC12IFGR0 &= ~ADC12IFG2;                           // clear inturrput flag on ADC12MEM2
		ADC12IFGR0 &= ~ADC12IFG3;                           // clear inturrput flag on ADC12MEM3
	}

	else
	{
		ADC12IFGR0 &= ~ADC12IFG0;                           // clear inturrput flag on ADC12MEM0
		ADC12IFGR0 &= ~ADC12IFG1;                           // clear inturrput flag on ADC12MEM1
		ADC12IFGR0 &= ~ADC12IFG2;                           // clear inturrput flag on ADC12MEM2
		ADC12IFGR0 &= ~ADC12IFG3;                           // clear inturrput flag on ADC12MEM3

		ADC12CTL0 |= ADC12SC;                               // start conversion
	}
}
