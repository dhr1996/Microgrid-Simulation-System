#include "WYLib28335.h"
#include "DSP28x_Project.h"

#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
 #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
 #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif

#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_SHCLK  0xf   // S/H width in ADC module periods


#define ADC_CASCADED 	0x1
#define ADC_DUAL	 	0x0
#define ADC_CONTINUOUS 	0x1
#define ADC_SINGLE		0x0

#define ADC_SEQ_SAMPLE  0x0
#define ADC_SIM_SAMPLE  0x1

#define ADC_ADCINA0  	0x0
#define ADC_ADCINA1  	0x1
#define ADC_ADCINA2  	0x2
#define ADC_ADCINA3  	0x3
#define ADC_ADCINA4  	0x4
#define ADC_ADCINA5  	0x5
#define ADC_ADCINA6  	0x6
#define ADC_ADCINA7  	0x7
#define ADC_ADCINB0  	0x8
#define ADC_ADCINB1  	0x9
#define ADC_ADCINB2  	0xA
#define ADC_ADCINB3  	0xB
#define ADC_ADCINB4  	0xC
#define ADC_ADCINB5  	0xD
#define ADC_ADCINB6  	0xE
#define ADC_ADCINB7  	0xF
#define ADC_ADCINAB0  	0x0
#define ADC_ADCINAB1  	0x1
#define ADC_ADCINAB2  	0x2
#define ADC_ADCINAB3  	0x3
#define ADC_ADCINAB4  	0x4
#define ADC_ADCINAB5  	0x5
#define ADC_ADCINAB6  	0x6
#define ADC_ADCINAB7  	0x7



// Configure ADC [Cascade & Sequential-sampling]
void Config_ADC(void)
{
	InitAdc();												// Initialize ADC module to known state: Bandgap Ref, etc.
															// -- ADC Clock Configuration
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;					// Set Hi-speed Clock Prescalar, HSPCLK=25 MHz
	EDIS;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;				// Set 4-bit ADC module clock precalar
	AdcRegs.ADCTRL1.all = 0;								// Clear ADCTRL1 Reg
	AdcRegs.ADCTRL1.bit.CPS = 0;							// Set 1-bit prescalar, ADCCLK = HSPCLK/(2*ADC_CKPS)/(CPS+1)
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK; 				// Set S/H clock pulse, SHCLK= ADCCLK
	AdcRegs.ADCTRL1.bit.SEQ_CASC = ADC_CASCADED;			// Set Sequencer Mode : ADC_CASCADED/ADC_DUAL

	AdcRegs.ADCTRL3.bit.SMODE_SEL = ADC_SEQ_SAMPLE;			// Set Sampling Mode: ADC_SEQ_SAMPLE/ADC_SIM_SAMPLE
	AdcRegs.ADCTRL1.bit.CONT_RUN = ADC_SINGLE;				// Set Running Mode: ADC_SINGLE/ADC_CONTINUOUS

	AdcRegs.ADCMAXCONV.all = 0x9;       					// Set Maximum Conversions : Simultaneous:7MAX, Sequential:15MAX
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ADC_ADCINA4; 			//
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ADC_ADCINA2; 			//
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ADC_ADCINA0; 		//
//	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ADC_ADCINA3; 		//
//	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = ADC_ADCINA4; 		//
//	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = ADC_ADCINA5; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV06 = ADC_ADCINB2; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV07 = ADC_ADCINB3; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ADC_ADCINB0; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ADC_ADCINB1; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV10 = ADC_ADCINB2; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV11 = ADC_ADCINB3;		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV12 = ADC_ADCINB4; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV13 = ADC_ADCINB5; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV14 = ADC_ADCINB6; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV15 = ADC_ADCINB7; 		//

	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;					// Enable SOCA from ePWM to start SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  					// Enable SEQ1 interrupt (every EOS)
	//AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;				// Enable SOCB from ePWM to start SEQ2
	//AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;  				// Enable SEQ2 interrupt (every EOS)


	return;
}


/*

// Configure ADC [Cascade & Simultaneous-sampling]
void Config_ADC(void)
{
	InitAdc();												// Initialize ADC module to known state: Bandgap Ref, etc.
															// -- ADC Clock Configuration
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;					// Set Hi-speed Clock Prescalar, HSPCLK=25 MHz
	EDIS;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;				// Set 4-bit ADC module clock precalar
	AdcRegs.ADCTRL1.all = 0;								// Clear ADCTRL1 Reg
	AdcRegs.ADCTRL1.bit.CPS = 0;							// Set 1-bit prescalar, ADCCLK = HSPCLK/(2*ADC_CKPS)/(CPS+1)
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK; 				// Set S/H clock pulse, SHCLK= ADCCLK
	AdcRegs.ADCTRL1.bit.SEQ_CASC = ADC_CASCADED;			// Set Sequencer Mode : ADC_CASCADED/ADC_DUAL

	AdcRegs.ADCTRL3.bit.SMODE_SEL = ADC_SEQ_SAMPLE;			// Set Sampling Mode: ADC_SEQ_SAMPLE/ADC_SIM_SAMPLE
	AdcRegs.ADCTRL1.bit.CONT_RUN = ADC_SINGLE;				// Set Running Mode: ADC_SINGLE/ADC_CONTINUOUS

	AdcRegs.ADCMAXCONV.all = 0x0001;       					// Set Maximum Conversions : Simultaneous:7MAX, Sequential:15MAX
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ADC_ADCINA0; 			//
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ADC_ADCINA1; 			//
	//AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ADC_ADCINA2; 		//
	//AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ADC_ADCINA3; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV04 = ADC_ADCINA4; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV05 = ADC_ADCINA5; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV06 = ADC_ADCINA6; 		//
	//AdcRegs.ADCCHSELSEQ2.bit.CONV07 = ADC_ADCINA7; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ADC_ADCINB0; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ADC_ADCINB1; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV10 = ADC_ADCINB2; 		//
	//AdcRegs.ADCCHSELSEQ3.bit.CONV11 = ADC_ADCINB3;		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV12 = ADC_ADCINB4; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV13 = ADC_ADCINB5; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV14 = ADC_ADCINB6; 		//
	//AdcRegs.ADCCHSELSEQ4.bit.CONV15 = ADC_ADCINB7; 		//

	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;					// Enable SOCA from ePWM to start SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  					// Enable SEQ1 interrupt (every EOS)
	//AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;					// Enable SOCB from ePWM to start SEQ2
	//AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;  					// Enable SEQ2 interrupt (every EOS)


	return;
}

*/


