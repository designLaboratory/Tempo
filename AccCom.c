#include "AccCom.h

uint8_t AccRegisterRead(uint8_t addr);
{
	uint8_t ack;
	uint8_t data;
	I2CWrite(AccSlaveAddr << 1);
	I2CWrite(addr);
	I2CRestart();
	ack = I2CWrite(AccSlaveAddr<<1 | 0x01);
	data = I2CRead(ack);
	return data;
}