#include "MKL46Z4.h"

void I2CInitialize(I2C_Type* i2c);

typedef enum{
I2C_ACK=0,
I2C_NACK=1,
}I2C_Acknowladge_Bit;



void I2C_En(I2C_Type* i2c);
void I2C_Dis(I2C_Type* i2c);

void I2C_En_Interrupt(I2C_Type* i2c);
void I2C_Dis_Interrupt(I2C_Type* i2c);

void I2C_Start(I2C_Type* i2c);
void I2C_Restart(I2C_Type* i2c);
void I2C_Stop(I2C_Type* i2c);

uint8_t I2C_Read_Byte(I2C_Type* i2c,uint8_t ack);
uint8_t I2C_Write_Byte(I2C_Type* i2c,uint8_t data);
