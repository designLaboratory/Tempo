#include "MKL46Z4.h"
#include "I2C.h"
#include "AccCom.h"
#include "slcd.h"

uint8_t data=11;

int main()
{
	I2CInitialize();
	slcdInitialize();
//	AccInitialize();
	I2CWriteRegister(0x1D,0x2A,0x01);
	data = I2CReadRegister(0x1D,0x0D);

	while (1)
	{
		data = I2CReadRegister(0x1D,0x01);
		slcdDisplay(data,16);
		delay_mc(100);
	}
	
	// 0;

}

