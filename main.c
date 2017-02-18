#include "MKL46Z4.h"
#include "I2C.h"
#include "AccCom.h"
#include "slcd.h"

uint8_t data=0;

void PORTC_PORTD_IRQHandler()
{
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	if ((FPTC->PDIR&(1 << 5)))
	{
		PORTC->PCR[5] |= PORT_PCR_IRQC_MASK;
		data++;
	}
}

int main()
{
	I2CInitialize();
	slcdInitialize();
	AccInitialize();
	AccInterruptInitialize();
	while (1)
	{
		slcdDisplay(data, 10);
		delay_ms(50);
	}
}

