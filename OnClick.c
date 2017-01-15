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
	
	tempoValue = 0;									// reset tempoValue
}

void Click(void)
{
	if (TPM1->SC&TPM_SC_TOF_MASK)					// when timer overflow
	{
		tempoValue = 0;								// tempo is less than 1BPM
		TPM1->CNT = 0;								// reset counter
		return;
	}
	uint16_t cntValue = TPM1->CNT;					// read counter value
	tempoValue = 60 * clkFreq / cntValue;			// assign tempoValue
	TPM1->CNT = 0;									// reset counter
}