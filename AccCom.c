#include "AccCom.h"

void AccInitialize()
{

//	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x00);	 // Standby mode   
//	I2CWriteRegister(MMA845x_I2C_ADDRESS, XYZ_DATA_CFG_REG, 0x00);		// +/-2g range -> 1g = 16384/4 = 4096 counts 
//	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x02);		// High Resolution mode
//	I2CWriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);	// ODR = 1.56Hz, Reduced noise, Active mode	
}
