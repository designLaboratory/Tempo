#include "I2C.h"

void I2CInitialize()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	PORTE->PCR[24] = PORT_PCR_MUX(6);
	PORTE->PCR[25] = PORT_PCR_MUX(6);

	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4_MASK(6);
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	I2C0->F = I2C_F_MULT(2) | I2C_F_ICR(0x05);
	I2C0->C1 |= I2C_C1_MST_MASK | I2C_C1_IICEN_MASK;
}

uint8_t I2CWrite(uint8_t data)
{

	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->S |= I2C_S_IICIF_MASK;

	I2C0->D = data;
	while (I2C0->S&I2C_S_IICIF_MASK);

	return ((I2C0->S & I2C_S_RXAK_MASK) == I2C_S_RXAK_MASK ? 1 : 0);
}

uint8_t I2CRead(uint8_t ack)
{
	I2C0->C1 &= ~I2C_C1_TX_MASK;

	if (!I2C0->SMB & I2C_SMB_FACK_MASK)
		I2C0->C1 = (ack == 1) ? I2C0->C1 | I2C_C1_TXAK_MASK : I2C0->C1 | ~I2C_C1_TXAK_MASK;

	I2C0->S |= I2C_S_IICIF_MASK;
	(void)I2C0->D;
	while (!I2C0->S&I2C_S_IICIF_MASK);
	
	if (!I2C0->SMB & I2C_SMB_FACK_MASK)
		I2C0->C1 = (ack == 1) ? I2C0->C1 | I2C_C1_TXAK_MASK : I2C0->C1 & ~I2C_C1_TXAK_MASK;

	I2C0->C1 |= I2C_C1_TX_MASK;

	return I2C0->D;
}

void I2CRestart() {
	I2C0->C1 |= I2C_C1_RSTA_MASK;
}

void I2CStart() {
	I2C0->C1 |= I2C_C1_MST_MASK;
}

void I2CStop() {
	I2C0->FLT |= I2C_FLT_STOPF_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK;

	while (!I2C0->FLT & I2C_FLT_STOPF_MASK)
		I2C0->C1 &= ~I2C_C1_MST_MASK;
}