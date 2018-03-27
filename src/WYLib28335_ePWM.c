#include "WYLib28335.h"
#include "DSP28x_Project.h"

// Stop all the TB clocks
void ePWM_TBCLK_SYNC_disable()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
}

// Start all the TB clocks synced
void ePWM_TBCLK_SYNC_enable()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}




/* EPWM Module 1 config */
void Init_ePWM1()
{
	InitEPwm1Gpio();
	EALLOW;
	//Timebase clock
	EPwm1Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV)
	
	//Timebase, Counter-mode, Phase-shift, etc.
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm1Regs.TBPRD = 1500;								// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm1Regs.TBPHS.half.TBPHS = 0; 					// Set Phase register
	EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [A]
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;		 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [B]
//	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm1Regs.AQCTLB.bit.CBD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm1Regs.DBFED = 15; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm1Regs.DBRED = 15; 								// RED = DBRED*t_TBCLK, 1==0.01us
	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm1Regs.TBCTR = 0;                      			// TBCTR
//	EPwm1Regs.CMPA.half.CMPA = 1000;     			    // CMPA
//	EPwm1Regs.CMPB = 500;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm1Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm1Regs.ETSEL.bit.SOCAEN	= 1;					// SOCA interrupt enable;
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm1Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm1Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm1Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;
}
/* END of EPWM Module 1 config */



/* EPWM Module 2 config */
void Init_ePWM2()
{
	InitEPwm2Gpio();
	EALLOW;
	//Timebase clock
	EPwm2Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm2Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV)
	
	//Timebase, Counter-mode, Phase-shift, etsc.
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm2Regs.TBPRD = 1500; 								// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm2Regs.TBPHS.half.TBPHS = 0; 					// Set Phase register
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [A]
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;		 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;    	 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [B]
//	EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm2Regs.AQCTLB.bit.CBD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm2Regs.DBFED = 15; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm2Regs.DBRED = 15; 								// RED = DBRED*t_TBCLK, 1==0.01us

	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm2Regs.TBCTR = 0;                      			// TBCTR
//	EPwm2Regs.CMPA.half.CMPA = 100;     					// CMPA
//	EPwm2Regs.CMPB = 500;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm2Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm2Regs.ETSEL.bit.SOCAEN	= 0;					// SOCA interrupt enable;
	EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm2Regs.ETPS.bit.SOCAPRD = ET_1ST;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm2Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm2Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm2Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;

}
/* END of EPWM Module 2 config */



/* EPWM Module 3 config */
void Init_ePWM3()
{
	InitEPwm3Gpio();
	EALLOW;
	//Timebase clock
	EPwm3Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm3Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV)
	
	//Timebase, Counter-mode, Phase-shift, etc.
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm3Regs.TBPRD = 1500; 								// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm3Regs.TBPHS.half.TBPHS = 0;//1128.0f/3.0f*2.0f; 					// Set Phase register
//	EPwm3Regs.TBPHS.half.TBPHS = 0;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
//	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [A]
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [B]
//	EPwm3Regs.AQCTLB.bit.CBU = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm3Regs.AQCTLB.bit.CBD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm3Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
//	EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm3Regs.DBFED = 15; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm3Regs.DBRED = 15; 								// RED = DBRED*t_TBCLK, 1==0.01us
	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm3Regs.TBCTR = 0;                      			// TBCTR
//	EPwm3Regs.CMPA.half.CMPA = 0;     					// CMPA
//	EPwm3Regs.CMPB = 0;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm3Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm3Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm3Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm3Regs.ETSEL.bit.SOCAEN	= 0;					// SOCA interrupt enable; 
	EPwm3Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm3Regs.ETPS.bit.SOCAPRD = ET_3RD;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm3Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm3Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm3Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm3Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm3Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm3Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm3Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;

}
/* END of EPWM Module 3 config */

















/* EPWM Module 4 config */
void Init_ePWM4()
{
	InitEPwm4Gpio();
	EALLOW;
	//Timebase clock
	EPwm4Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm4Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV) =97656Hz
	
	//Timebase, Counter-mode, Phase-shift, etc.
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm4Regs.TBPRD = 1500; 						// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm4Regs.TBPHS.half.TBPHS = 0; 					// Set Phase register
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [A]
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLA.bit.CAD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [B]
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLB.bit.CBD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm4Regs.AQCTLB.bit.PRD = AQ_TOGGLE; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm4Regs.DBFED = 50; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm4Regs.DBRED = 50; 								// RED = DBRED*t_TBCLK, 1==0.01us
	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm4Regs.TBCTR = 0;                      			// TBCTR
	EPwm4Regs.CMPA.half.CMPA = 750;     					// CMPA
	EPwm4Regs.CMPB = 750;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm4Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm4Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm4Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm4Regs.ETSEL.bit.SOCAEN	= 0;					// SOCA interrupt enable;
	EPwm4Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPA;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm4Regs.ETPS.bit.SOCAPRD = ET_1ST;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm4Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm4Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm4Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm4Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm4Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm4Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm4Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;

}

/* END of EPWM Module 4 config */


void Init_ePWM5()
{
	InitEPwm5Gpio();
	EALLOW;
	//Timebase clock
	EPwm5Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV)
	
	//Timebase, Counter-mode, Phase-shift, etc.
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm5Regs.TBPRD = 15000; 								// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm5Regs.TBPHS.half.TBPHS = 0; 					// Set Phase register
	EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
	EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [B]
	EPwm5Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;		 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;		 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;    	 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLB.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [A]
	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLA.bit.CBU = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm5Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm5Regs.DBFED = 20; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm5Regs.DBRED = 20; 								// RED = DBRED*t_TBCLK, 1==0.01us
	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm5Regs.TBCTR = 0;                      			// TBCTR
	EPwm5Regs.CMPA.half.CMPA = 3000;     					// CMPA
	EPwm5Regs.CMPB = 0;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm5Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm5Regs.ETSEL.bit.SOCAEN	= 0;					// SOCA interrupt enable; 
	EPwm5Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm5Regs.ETPS.bit.SOCAPRD = ET_1ST;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm5Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm5Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm5Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm1Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm1Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;

}



/* EPWM Module 2 config */
//#pragma DATA_SECTION(Init_ePWM6,"EPWM6PZ");
void Init_ePWM6()
{
	InitEPwm6Gpio();
	EALLOW;
	//Timebase clock
	EPwm6Regs.TBCTL.bit.HSPCLKDIV =0;       			// High-speed clock prescalar HSPCLKDIV: 0x0=1,0x1=2,0x2=4,0x3=6...0x7=14 
	EPwm6Regs.TBCTL.bit.CLKDIV = 0;         			// Timebase clock prescalar CLKDIV=2^N; 
														// TBCLK= SYSCLKOUT/(HSPCLKDIV*CLKDIV)
	
	//Timebase, Counter-mode, Phase-shift, etc.
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 		// TB_COUNT_UPDOWN/TB_COUNT_UP/TB_COUNT_DOWN/TB_COUNT_FREEZE
	EPwm6Regs.TBPRD = 15000;						// Period = TBPRD*TBCLK counts (for updown,additionaly*2); Switching frequency= PWMCLK/TBPRD
	EPwm6Regs.TBPHS.half.TBPHS = 0; 					// Set Phase register
	EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE; 			// TB_DISABLE=Master module TB_ENABLE=Slave module
	EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;  			// TB_SHADOW/TB_IMMEDIATE
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// TB_CTR_ZERO/TB_CTR_CMPB/TB_SYNC_IN=Sync down-stream module; TB_SYNC_DISABLE=Sync disable
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// CC_SHADOW/CC_IMMEDIATE
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;			// CC_SHADOW/CC_IMMEDIATE
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD; 		// CC_CTR_ZERO/CC_CTR_PRD/CC_CTR_ZERO_PRD/CC_LD_DISABLE

	//ePWM Actions [B]
	EPwm6Regs.AQCTLB.bit.CAU = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLB.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLB.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Actions [A]
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE
	EPwm6Regs.AQCTLA.bit.CBU = AQ_NO_ACTION; 			// AQ_NO_ACTION/AQ_CLEAR/AQ_SET/AQ_TOGGLE

	//ePWM Deadband
	EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// DBA_ALL /DBB_RED_DBA_FED/DBA_RED_DBB_FED/DBB_ALL
	EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 			// DB_DISABLE/DBA_ENABLE/DBB_ENABLE/DB_FULL_ENABLE
	EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 			// DB_ACTV_HI/DB_ACTV_LOC/DB_ACTV_HIC/DB_ACTV_LO
	EPwm6Regs.DBFED = 20; 								// FED = DBFED*t_TBCLK, 1==0.01us
	EPwm6Regs.DBRED = 20; 								// RED = DBRED*t_TBCLK, 1==0.01us
	
	//ePWM Chopper
	//Never used in a digital power supply
	
	//ePWM Trip-Zone
	//Not constructed in Version1
	
	//ePWM Counter/Compare Initialization
	EPwm6Regs.TBCTR = 0;                      			// TBCTR
	EPwm6Regs.CMPA.half.CMPA = 0;     					// CMPA
	EPwm6Regs.CMPB = 1000;     							// CMPB
	
	//ePWM Event-Trigger
														// ---ePWM interrupt
	EPwm6Regs.ETSEL.bit.INTEN = 0;                      // EPWMxINT interrupt enable; 
	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;			// trigger source of EPWMxINT : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;						// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.INT = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.INT = 1;						// clear EPWMxINT flag [DO NOT FORGET]
														// ---SoC_A interrupt
	EPwm6Regs.ETSEL.bit.SOCAEN	= 0;					// SOCA interrupt enable;
	EPwm6Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm6Regs.ETPS.bit.SOCAPRD = ET_1ST;				// every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.SOCA = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.SOCA = 1;						// clear SOCA flag [DO NOT FORGET]
														// ---SoC_B interrupt
	EPwm6Regs.ETSEL.bit.SOCBEN	= 0;					// SOCB interrupt enable; 
	EPwm6Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;			// trigger source of SOCA : ET_CTR_ZERO/ET_CTR_PRD/ET_CTRU_CMPA/ET_CTRD_CMPA/ET_CTRU_CMPB/ET_CTRD_CMPB
	EPwm6Regs.ETPS.bit.SOCBPRD = ET_1ST;			    // every ? event(s) : ET_DISABLE/ET_1ST/ET_2ND/ET_3RD
	//EPwm2Regs.ETFRC.bit.SOCB = 0;						// software force trigger [USEFUL IN DEBUG]
	//EPwm2Regs.ETCLR.bit.SOCB = 1;						// clear SOCA flag [DO NOT FORGET]	
	EDIS;

}


