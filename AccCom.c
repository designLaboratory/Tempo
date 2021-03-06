#include "AccCom.h"

void AccInitialize()
{
	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x08); // acc in sleep mode
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
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_CFG_REG, 0x15); //single tap detect
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSX_REG, 0x20); // X threshold 
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSY_REG, 0x20); // Y threshold 
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_THSZ_REG, 0x2A); // Z threshold 
	//I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_TMLT_REG, 0xA0); // pulse time limit 
	I2CWriteRegister(MMA845x_I2C_ADDRESS, PULSE_LTCY_REG, 0xF0); // pulse latency

	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 0x08); //enable interrupt for pulse
	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 0x08); //interrupt on int1
}

void AccInterruptInitialize()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; // portC clk
	PORTC->PCR[5] |= PORT_PCR_MUX(1); // ptc5 gpio
	PORTC->PCR[5] |= PORT_PCR_PE_MASK;// pull down resistor
	PORTC->PCR[5] |= PORT_PCR_IRQC(9); // rising edge interrupt
	
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);	
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);
}

