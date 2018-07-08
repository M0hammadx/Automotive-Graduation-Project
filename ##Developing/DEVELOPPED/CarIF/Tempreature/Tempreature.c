/*
 * Tempreature.c
 *
 *  Created on: Jun 13, 2018
 *      Author: Mohab
 */
#include "Tempreature.h"
/* -----------------------      Global Variables        --------------------- */
static uint32_t ui32ADC0Value[8];                  // Array to store the ADC values
static volatile uint32_t ui32TempAvg;              // Variable to store the Average of ADC values
static volatile uint32_t ui32TempValueC;           // Variable to store the Temperature in celsius
static volatile uint32_t ui32TempValueF;           // Variable to store the Temperature in fahrenheit


void TempreatureSensor_Init(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}; //wait until clock stable

    // Enable hardware averaging on ADC0
    ROM_ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    // Configure to use ADC0, sample sequencer 0, processor to trigger sequence and use highest priority
    ROM_ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    // Configure all 8 steps on sequencer 0 to sample temperature sensor
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_TS);
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_TS);
    // Mark as last conversion on sequencer 0 and enable interrupt flag generation on sampling completion
    ROM_ADCSequenceStepConfigure(ADC0_BASE, 0, 7,
                                 ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);

    // Enable Sequencer 0
    ROM_ADCSequenceEnable(ADC0_BASE, 0);
}


void Temprature_Get_Temp(uint8_t* CarTemp){
    // Clear the ADC Interrupt (if any generated) for Sequencer 0
           ROM_ADCIntClear(ADC0_BASE, 0);
           // Trigger the ADC Sampling for Sequencer 0
           ROM_ADCProcessorTrigger(ADC0_BASE, 0);
           // Wait the program till the conversion isn't complete
           while(!ROM_ADCIntStatus(ADC0_BASE, 0, false));
           // Store the values in sequencer 0 of ADC0 to an Array
           ROM_ADCSequenceDataGet(ADC0_BASE, 0, ui32ADC0Value);
           // Calculate the Average of the Readings
           ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3]
                   + ui32ADC0Value[4] + ui32ADC0Value[5] + ui32ADC0Value[6] + ui32ADC0Value[6] + 4)/8;
           // Convert the reading to Celsius and Fahrenheit values
           ui32TempValueC = (1475 - ((2475 * ui32TempAvg)) / 4096)/10;
           //ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;
           *CarTemp =  (uint8_t)ui32TempValueC;
}

