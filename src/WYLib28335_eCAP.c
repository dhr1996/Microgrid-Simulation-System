#include "WYLib28335.h"
#include "DSP28x_Project.h"

/* ECAP Module 1 config */
void Init_eCAP1()
{
	InitECap1Gpio();
	ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
	ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
	ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

    // Configure peripheral registers
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_ONESHOT;      // One-shot
    ECap1Regs.ECCTL2.bit.STOP_WRAP = EC_EVENT1;        // Stop at 1 events
    ECap1Regs.ECCTL1.bit.CAP1POL = EC_FALLING;          // Rising edge
//	ECap1Regs.ECCTL1.bit.CAP2POL = EC_RISING;          // Rising edge
//  ECap1Regs.ECCTL1.bit.CAP3POL = EC_FALLING;          // Falling edge
//	ECap1Regs.ECCTL1.bit.CAP4POL = EC_RISING;          // Rising edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;          // Difference operation
//	ECap1Regs.ECCTL1.bit.CTRRST2 = 1;          // Difference operation
//	ECap1Regs.ECCTL1.bit.CTRRST3 = 1;          // Difference operation
//	ECap1Regs.ECCTL1.bit.CTRRST4 = 1;          // Difference operation
	ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
	ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
	ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units


	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
	ECap1Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
	ECap1Regs.ECEINT.bit.CEVT1 = 1;            // 4 events = interrupt
}
/* END of ECAP Module 1 config */


/* ECAP Module 2 config */
void Init_eCAP2()
{
	InitECap2Gpio();
	ECap2Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
	ECap2Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
	ECap2Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

    // Configure peripheral registers
    ECap2Regs.ECCTL2.bit.CONT_ONESHT = EC_ONESHOT;      // One-shot
    ECap2Regs.ECCTL2.bit.STOP_WRAP = EC_EVENT1;        // Stop at 1 events
    ECap2Regs.ECCTL1.bit.CAP1POL = EC_FALLING;          // Rising edge
//	ECap2Regs.ECCTL1.bit.CAP2POL = EC_RISING;          // Rising edge
//  ECap2Regs.ECCTL1.bit.CAP3POL = EC_FALLING;          // Falling edge
//	ECap2Regs.ECCTL1.bit.CAP4POL = EC_RISING;          // Rising edge
    ECap2Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;          // Difference operation
//	ECap2Regs.ECCTL1.bit.CTRRST2 = 1;          // Difference operation
//	ECap2Regs.ECCTL1.bit.CTRRST3 = 1;          // Difference operation
//	ECap2Regs.ECCTL1.bit.CTRRST4 = 1;          // Difference operation
	ECap2Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
	ECap2Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
	ECap2Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units


	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
	ECap2Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
	ECap2Regs.ECEINT.bit.CEVT1 = 1;            // 4 events = interrupt
}
/* END of ECAP Module 2 config */
