#include "I2C.h"
#include "MKL46Z4.h"

#define AccSlaveAddr 0x1D
#define AccXRegMSBAddr 0x01

uint8_t AccRegisterRead(uint8_t addr);