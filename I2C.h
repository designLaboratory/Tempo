#include "MKL46Z4.h"

void I2CInitialize(void);
uint8_t I2CWrite(uint8_t data);
uint8_t I2CRead(uint8_t ack);
void I2CStop(void);
void I2CStart(void);
void I2CRestart(void);