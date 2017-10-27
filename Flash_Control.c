#include "Flash_Control.h"
#include "protocol.h"
#include "EEPROM.h"

uint32_t Flash_Times = 0;
uint8_t Flash_Flag = 0;
uint8_t Flash_Ready_OK_Flag = 0;
uint8_t Flash_Off_Flag = 0;
uint8_t Flash_OK_Flag = 0;
uint8_t Flash_Level = 0;
uint8_t EEPROM_Write_Number_Error;
uint8_t Check_Write_EEPROM_Timeout = 0;

extern uint8_t Recive_Buff[10];
extern uint8_t Recive_Buffer_Full_Flag;

void Flash_IO_Init(void)
{
	P07 = 0; //Trig Off;
	P01 = 0; //Full_charge LED Off;
	P0M |= 0x82;  //trig pin, full charge pin out mode;
	P0UR &= ~0x82; //disable pull up; 
}

void Flash_Control(uint8_t flash_times)
{
	while(!Flash_Ready_OK_Flag)
	{
		while(!Recive_Buffer_Full_Flag);
		Recive_Buffer_Full_Flag = 0;
		if(Recive_Buff[0] == FUN_No4)
		{
			Send_Data(&Flash_Flag,1);
		}
		if(Recive_Buff[0] == FUN_No9)
		{
			Flash_Ready_OK_Flag = Recive_Buff[2];
		}
		//error_check;
	}
	Recive_Buffer_Full_Flag = 0;
	while(flash_times)
	{
		Trig_On;
		while(!Flash_Off_Flag)
		{
			while(!Recive_Buffer_Full_Flag);
			Recive_Buffer_Full_Flag = 0;
			if(Recive_Buff[0] == FUN_No10)
			{
				Flash_Off_Flag = Recive_Buff[2];
			}
		}
		Trig_Off;
		flash_times--;
	}
	while(Flash_OK_Flag)
	{
		while(!Recive_Buffer_Full_Flag);
		Recive_Buffer_Full_Flag = 0;
		if(Recive_Buff[0] == FUN_No10)
		{
			Flash_OK_Flag = Recive_Buff[2];
		}
	}
	Recive_Buffer_Full_Flag = 0;
	if(Flash_Level <= 2)
	{
		Flash_Times ++;
	}else{
		if(Flash_Level <= 5)
		{
			Flash_Times += 3;
		}else{
			Flash_Times += 5;
		}
	}
	Write_Num_TO_EEPROM(Flash_Times);//write data to eeprom, disable write;
	while(Flash_Times != Read_Num_From_EEPROM())
	{
		Check_Write_EEPROM_Timeout++;
		//IWDG->KR = 0xAA;
		Write_Num_TO_EEPROM(Flash_Times);
		if(Check_Write_EEPROM_Timeout == 20)
		{
			EEPROM_Write_Number_Error = 1;
			return;
		}
	}
	EEPROM_Write_Number_Error = 0;
}