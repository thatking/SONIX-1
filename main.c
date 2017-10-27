//#include "main.h"
//#include "protocol.h"
#include "SN8F5702.H"
#include "delay.h"
#include "UART.h"
#include "protocol.h"
#include "ADC.h"
#include "EEPROM.h"

extern uint8_t Recive_Buffer_Full_Flag;
extern uint8_t Recive_Buff[10];
extern uint8_t Recevie_Date_Length;

void main(void)
{
	uint8_t z[5]={'a','b','c','d',8};
	uint8_t Data_Check_OK,sr;
	uint32_t readdata;
	CLKSEL = 0x07; //set fcpu = fosc/8
  CLKCMD = 0x69; //Apply CLKSEL’s setting
	WDTR = 0x5A;
	Delay_Init();
	Uart_Init();
	ADC_Init_Fun();
	EEPROM_IO_Init();
	IEN0 |= 0x80;
	P07 = 0;
	P0M = 0x80;
	//Send_Data(&z,5);
	while(1)
	{	
		sr = EEPROM_Read_SR();
		Uart_SendByte(sr);
		readdata = Read_Num_From_EEPROM();
		Uart_SendStr(&readdata);
		//Write_Num_TO_EEPROM(3);
		if(Recive_Buffer_Full_Flag)
		{
			Recive_Buffer_Full_Flag = 0;
			Uart_SendStr(&Recive_Buff);
			Data_Check_OK = Receive_Data_Check(&Recive_Buff,Recevie_Date_Length);		
      Uart_SendByte(Data_Check_OK);			
			if(!Data_Check_OK)
		  {
				Send_Data(&Data_Check_OK,1);
			}
		}
		//readdata = ADC_Read_Channel_Fun(ADC_FAN_CHANNEL);
		//Uart_SendStr(&readdata);
		Delay_ms(500);
	}
}
