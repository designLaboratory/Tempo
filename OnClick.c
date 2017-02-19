#include "OnClick.h"

const uint16_t clkFreq = 1000;

void OnClickInitialize(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;				// TPM1 CLK enabled
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);				// TPM1 CLK source MCGIRCLK
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;					// internal CLK reference enabled
	MCG->C1 |= MCG_C1_IREFS_MASK;					// slow internal CLK reference

	TPM1->CnSC |= TPM_CnSC_MSA_MASK;				// software compare mode
	TPM1->SC |= TPM_SC_PS(5);						// prescaler value 32
	TPM1->CNT = 0;									// reset counter
	TPM1->MOD = 60 * clkFreq;						// modulo when 1 BPM
	TPM1->SC |= TPM_SC_CMOD(1);						// counter increment on clk
}

uint16_t Click(void)
{
	if (TPM1->SC&TPM_SC_TOF_MASK)					// when timer overflow
	{
		TPM1->CNT = 0;								// reset counter
		return 0;									// return tempo is less than 1BPM
	}
	uint16_t cntValue = TPM1->CNT;					// read counter value
	TPM1->CNT = 0;									// reset counter
	if (cntValue == 0)								// if time is less than timer lsb
		return 0xffff;								// return max value
	return 60 * clkFreq / cntValue;					// return tempo value
	
}