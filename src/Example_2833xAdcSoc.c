// TI File $Revision: /main/11 $
// Checkin $Date: April 21, 2008   15:41:01 $
//###########################################################################
//
// FILE:   Example_2833xAdc.c
//
// TITLE:  DSP2833x ADC Example Program.
//
// ASSUMPTIONS:
//
//   This program requires the DSP2833x header files.
//
//   Make sure the CPU clock speed is properly defined in
//   DSP2833x_Examples.h before compiling this example.
//
//   Connect signals to be converted to A2 and A3.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2833x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//       $Boot_Table:
//
//         GPIO87   GPIO86     GPIO85   GPIO84
//          XA15     XA14       XA13     XA12
//           PU       PU         PU       PU
//        ==========================================
//            1        1          1        1    Jump to Flash
//            1        1          1        0    SCI-A boot
//            1        1          0        1    SPI-A boot
//            1        1          0        0    I2C-A boot
//            1        0          1        1    eCAN-A boot
//            1        0          1        0    McBSP-A boot
//            1        0          0        1    Jump to XINTF x16
//            1        0          0        0    Jump to XINTF x32
//            0        1          1        1    Jump to OTP
//            0        1          1        0    Parallel GPIO I/O boot
//            0        1          0        1    Parallel XINTF boot
//            0        1          0        0    Jump to SARAM	    <- "boot to SARAM"
//            0        0          1        1    Branch to check boot mode
//            0        0          1        0    Boot to flash, bypass ADC cal
//            0        0          0        1    Boot to SARAM, bypass ADC cal
//            0        0          0        0    Boot to SCI-A, bypass ADC cal
//                                              Boot_Table_End$
//
// DESCRIPTION:
//
//   This example sets up the PLL in x10/2 mode.
//
//   For 150 MHz devices (default)
//   divides SYSCLKOUT by six to reach a 25.0Mhz HSPCLK
//   (assuming a 30Mhz XCLKIN).
//
//   For 100 MHz devices:
//   divides SYSCLKOUT by four to reach a 25.0Mhz HSPCLK
//   (assuming a 20Mhz XCLKIN).
//
//   Interrupts are enabled and the ePWM1 is setup to generate a periodic
//   ADC SOC on SEQ1. Two channels are converted, ADCINA3 and ADCINA2.
//
//   Watch Variables:
//
//         Voltage1[10]     Last 10 ADCRESULT0 values
//         Voltage2[10]     Last 10 ADCRESULT1 values
//         ConversionCount  Current result number 0-9
//         LoopCount        Idle loop counter
//
//
//###########################################################################
//
// Original Author: D.F.
//
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_2833xAdcSoc.h"

#define ADC_CKPS   0x1   // ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_SHCLK  0x2   // S/H width in ADC module periods                        //= 16 ADC clocks 采样窗口
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

// Prototype statements for functions found within this file.
interrupt void adc_isr(void);

// Global variables used in this example:
/*Uint16 LoopCount;
Uint16 ConversionCount;
Uint16 Voltage1[10];
Uint16 Voltage2[10];
*/

void configure_adc()
{

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
//   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
//   IER = 0x0000;
//   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
//   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//  EALLOW;  // This is needed to write to EALLOW protected register
//   PieVectTable.ADCINT = &adc_isr;
//   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
//   InitAdc();  // For this example, init the ADC

// Step 5. User specific code, enable interrupts:

// Enable ADCINT in PIE
//   PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
/*   IER |= M_INT1; // Enable CPU Interrupt 1
   EINT;          // Enable Global interrupt INTM
   ERTM;          // Enable Global realtime interrupt DBGM

   LoopCount = 0;
   ConversionCount = 0;*/

//ADC 初始化配置程序
	// Configure ADC
	 //adc采样，采用双排列模式,同步采样,启/停方式,epwm触发方式
	   AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
	   AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
/*
//1.原来设想的方式 双排列同步采样
	   AdcRegs.ADCTRL1.bit.SEQ_CASC= 0;       //双排列模式
	   AdcRegs.ADCTRL3.bit.SMODE_SEL= 1;     //同步采样模式

	   AdcRegs.ADCMAXCONV.all = 0x0003;       // Setup 8 conv's on SEQ1 SEQ2
	   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; // Setup ADCINA0 ADCINB0 as 1st SEQ1 SEQ2conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1; // Setup ADCINA1 ADCINB1 as 2nd SEQ1 SEQ2conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2; // Setup ADCINA2 ADCINB2 as 3rd SEQ1 SEQ2conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3; // Setup ADCINA3 ADCINB3 as 4th SEQ1 SEQ2conv.
	 //注意转换结果的存放; 见书P137  ???

	   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
	   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;  // Enable SEQ2 interrupt (every EOS)

*/
//2.简单实现的方式 级联顺序采样
	   AdcRegs.ADCTRL1.bit.SEQ_CASC= 1;       //级联模式
	   AdcRegs.ADCTRL3.bit.SMODE_SEL= 0;      //顺序采样模式

	   //电压电流通道采样逐次进行采样				电压电流各4路通道

	   AdcRegs.ADCMAXCONV.all = 0x0009;       // Setup 8 conv's on SEQ
	   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; // Setup ADCINA0  as 1st SEQ conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x8; // Setup ADCINB0  as 2nd SEQ conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x1; // Setup ADCINA1  as 3rd SEQ conv.
	   AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x9; // Setup ADCINB1  as 4th SEQ conv.
	   AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x2; // Setup ADCINA2  as 5th SEQ conv.
	   AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0xA; // Setup ADCINB2  as 6th SEQ conv.
	   AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x3; // Setup ADCINA3  as 7th SEQ conv.
	   AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0xB; // Setup ADCINB3  as 8th SEQ conv.
	   AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x4; // Setup ADCINA4  as 7th SEQ conv.
	   AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0xC; // Setup ADCINB4  as 8th SEQ conv.

/*
	   //电压电流通道采样,****************只有一路通道
	   AdcRegs.ADCMAXCONV.all = 0x0001;       // Setup 2 conv's on SEQ
	   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x1; // Setup ADCINA0  as 1st SEQ conv.		ADCINA1

	   AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x8; // Setup ADCINB0  as 2nd SEQ conv.
*/
	   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
	   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)


	   //Epwm触发方式
	// Assumes ePWM1 clock is already enabled in InitSysCtrl();
//	   EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
//	   EPwm1Regs.ETSEL.bit.SOCASEL = 1;       // Select SOC from from ZERO on upcount
//	   EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

}








