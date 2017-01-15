#include "I2C.h"

uint8_t I2C_Write_Byte(I2C_Type* i2c,uint8_t data)
{
	//wlaczenie trybu transmisji
i2c->C1|=I2C_C1_TXAK_MASK;
	// usuniecie flagi IICIF
i2c->S|=I2C_S_IICIF_MASK;
	//Inicjalizacja przesylu danych
i2c->D=data;
	//oczekiwanie na zakonczenie przesylu
while(i2c->S && I2C_S_IICIF_MASK==0);//?? nie jestem pewnien czy dobrze

//Zwracanie otrzymanego bitu ACK
return ((i2c->S&I2C_S_RXAK_MASK)==I2C_S_RAM_MASK ? I2C_NACK:I2C_ACK);



}
uint8_t I2C_Read_Byte(I2C_Type* i2c,uint8_t ack)
{
	//Wybor trybu odbioru
	i2c->C1&=~I2C_C1_TX_MASK;
	//przygotowanie bitu ACK/NACK gdy FACK==0
	if((i2c->SMB&I2C_SMB_FACK_MASK)==0)
		i2c->C1=(ack==I2C_NACK)?i2c->C1|I2C_C1_TXAK_MASK:i2c->C1&~I2C_C1_TXAK_MASK;

//czyszczenie flagi IICIF
	i2c->S|=I2C_S_IICIF_MASK;
	//inicjalizacja przesylu danych
	i2c->D;
	//oczekiwanie na zakonczenie transferu
	while((i2c->S&I2C_S_IICIF_MASK)==0);
	
	if((i2c->SMB&I2C_SMB_FACK_MASK)!=0)
		i2c->C1=(ack==I2C_NACK)? i2c->C1|I2C_C1_TXAK_MASK:i2c->C1&~I2C_C1_TXAK_MASK;
	
	//przejscie do trybu transmisji
	i2c->C1|=I2C_C1_TXAK_MASK;
	
	//zwrocenie odebranych danych
	return i2c->D;	
}

void I2C_En(I2C_Type* i2c)
{
	i2c->C1|=I2C_C1_IICEN_MASK;
}
void I2C_Dis(I2C_Type* i2c)
{
	i2c->C1&=~I2C_C1_IICEN_MASK;
}

void I2C_En_Interrupt(I2C_Type* i2c)
{
	I2C0->C1|=I2C_C1_IICIE_MASK;
}
void I2C_Dis_Interrupt(I2C_Type* i2c)
{
	I2C0->C1&=~I2C_C1_IICIE_MASK;
}
void I2C_Start(I2C_Type* i2c)
{
	i2c->C1|=I2C_C1_MST_MASK;
}
void I2C_Restart(I2C_Type* i2c)
{
	i2c->C1|=I2C_C1_RSTA_MASK;
	
}
void I2C_Stop(I2C_Type* i2c)
{
	i2c->C1&=~I2C_C1_MST_MASK;
}

void InitializeI2c(I2C_Type* i2c)
{
	// Wlacz s. taktujacy interfejs I2C1
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;  
	// Wlacz s. taktujacy dla portu E
  SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;        
	//Przypisz jako  SCL
	PORTE->PCR[24]=PORT_PCR_MUX(6);
	//Przypisz pin jako  SDA
	PORTE->PCR[25]=PORT_PCR_MUX(6);
	
	I2C_En(i2c);
	I2C_En_Interrupt(i2c);
	I2C_Start(i2c);

}