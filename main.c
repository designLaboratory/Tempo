#include "MKL46Z4.h"
#include "I2C.h"
#include "AccCom.h"
#include "slcd.h"
#include "OnClick.h"

uint16_t tempoValue=0;

void PORTC_PORTD_IRQHandler()
{
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	if ((FPTC->PDIR&(1 << 5)))
	{
		PORTC->PCR[5] |= PORT_PCR_ISF_MASK;
		I2CReadRegister(MMA845x_I2C_ADDRESS, INT_SOURCE_REG);
		I2CReadRegister(MMA845x_I2C_ADDRESS, PULSE_SRC_REG);
		tempoValue=Click();
	}
}

int main()
{
	I2CInitialize();
	slcdInitialize();
	AccInitialize();
	AccInterruptInitialize();
	OnClickInitialize();
	while (1)
	{
		slcdDisplay(tempoValue, 10);
		delay_mc(50);
	}
}

