#include "MKL46Z4.h"

void I2CInitialize(void);
uint8_t I2CWrite(uint8_t data);
uint8_t I2CRead(uint8_t ack);
void I2CStop(void);
void I2CStart(void);
void I2CWait(void);
void I2CWriteRegister(uint8_t slaveAddr,uint8_t registerAddr,uint8_t data);
uint8_t I2CReadRegister(uint8_t slaveAddr,uint8_t registerAddr);
void I2CReStart(void);
