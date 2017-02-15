#include "I2C.h"

void I2CInitialize()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //zegar do portu

	PORTE->PCR[24] = PORT_PCR_MUX(5);
	PORTE->PCR[25] = PORT_PCR_MUX(5);

//	SIM->CLKDIV1|=SIM_CLKDIV1_OUTDIV4(7);//dzielenie bus clock przez 8
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;// zegar do IIC
	
	I2C0->F = 0x14;//I2C_F_MULT(2) | I2C_F_ICR(0x16); //icr i mult okreslaja szybkosc transmisjii mul=4
	
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	
}

void I2CWait()
{
	while(!(I2C0->S & I2C_S_IICIF_MASK)); 
	I2C0->S |= I2C_S_IICIF_MASK;
}

void CLKWait(int value)
{
	int i;
	for(i=0; i<value; i++)
	{
	};
}

void I2CWriteRegister(uint8_t slaveAddr,uint8_t registerAddr,uint8_t data)
{
	I2CStart();
	I2C0->D = slaveAddr<<1;
	I2CWait();
	I2C0->D = registerAddr;
	I2CWait();
	I2C0->D = data;
	I2CWait();
	I2CStop();
	
	CLKWait(50);
}	

uint8_t I2CReadRegister(uint8_t slaveAddr,uint8_t registerAddr)
{
	uint8_t data;
	
	I2CStart();
	I2C0->D = slaveAddr<<1;
	I2CWait();
	I2C0->D = registerAddr;
	I2CWait();
	I2CReStart();
	I2C0->D = slaveAddr<<1 | 0x01;
	I2CWait();
	
	I2C0->C1 &= ~I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_TXAK_MASK;
	(void)I2C0->D;
	I2CWait();
	data = I2C0->D;
	I2CWait();
	I2CStop();
	
	CLKWait(50);
	
	return data;
}
void I2CReStart()
{
	I2C0->C1 |= I2C_C1_RSTA_MASK;
}

void I2CStart() {
	I2C0->C1 |= I2C_C1_TX_MASK;
  I2C0->C1 |= I2C_C1_MST_MASK;

}

void I2CStop() {
	I2C0->C1 &= ~I2C_C1_MST_MASK;
  I2C0->C1 &= ~I2C_C1_TX_MASK;

}
