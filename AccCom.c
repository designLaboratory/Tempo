#include "AccCom.h"

void AccInitialize()
{
	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x00); // acc in sleep mode
	AccSingleTapSetup();
	AccSetActive();
}

void AccSetActive()
{
	uint8_t CTRL_DATA = I2CReadRegister(MMA845x_I2C_ADDRESS, CTRL_REG1); // read ctrl1 register from acc
	CTRL_DATA |= 0x01; // set active mode
	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, CTRL_DATA); // write register to acc
}

void AccSingleTapSetup()
{
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_CFG_REG, 0b01010101); //single tap detect
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSX_REG, 0x18); // X threshold 1.5g
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSY_REG, 0x18); // Y threshold 1.5g
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSZ_REG, 0x27); // Z threshold 2.5g
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_TMLT_REG, 0xA0); // pulse time limit 
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_LTCY_REG, 0xF0); // pulse latency

	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 1<<3); //enable interrupt for pulse
	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 1<<3); //interrupt on int1
}

void AccInterruptInitialize()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; // portC clk
	PORTC->PCR[5] |= PORT_PCR_MUX(1); // ptc5 gpio
	PORTC->PCR[5] |= PORT_PCR_IRQC(9); // rising edge interrupt
	
	NVIC_ClearPendingIRQ(PORTC_D_IRQn);	
	NVIC_EnableIRQ(PORTC_D_IRQn);
}

