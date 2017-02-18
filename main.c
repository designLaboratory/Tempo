#include "MKL46Z4.h"
#include "I2C.h"
#include "AccCom.h"
#include "slcd.h"

uint8_t data=0;

void PORTC_D_IRQHandler()
{
	NVIC_ClearPendingIRQ(PORTC_D_IRQn);
	if(PORTC->PTD[5])
	data++;
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

