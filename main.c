#include "MKL46Z4.h"
#include "I2C.h"
#include "AccCom.h"
#include "slcd.h"

uint8_t data;

int main()
{
	I2CInitialize();
	sLCDInitialize();
	data = AccRegisterRead(AccXRegMSBAddr);
	while (1)
	{
		slcdDisplay(data);
	}
	
	return 0;

}