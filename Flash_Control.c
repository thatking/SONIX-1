#include "Flash_Control.h"
#include "protocol.h"
#include "EEPROM.h"
#include "UART.h"

uint32_t Flash_Times = 0;
uint8_t Flash_Level = 0;


uint8_t Flash_Ready_OK_Flag = 0;
uint8_t Flash_Off_Flag = 0;


uint8_t EEPROM_Write_Number_Error;
uint8_t Check_Write_EEPROM_Timeout = 0;

extern uint8_t Receive_Buff[10];
extern uint8_t Receive_Buffer_Full_Flag;
extern uint8_t Receive_Buffer_Full_Flag;

void Flash_IO_Init(void)
{
	P07 = 0; //Trig Off;
	P01 = 0; //Full_charge LED Off;
	P0M |= 0x82;  //trig pin, full charge pin out mode;
	P0UR &= ~0x82; //disable pull up; 
}

void Flash_Control(uint8_t flash_times)
{
	uint16_t Time_Out = 100;
	uint8_t Data_Check_OK;
	uint8_t flash_request = 0;
	uint8_t Flash_Flag = 1;
  uint8_t Trig_Flag = 1;
	uint8_t Flash_OK_Flag = 0;
	while(flash_times)
	{
		Time_Out = 50000;
		while(!flash_request)
		{
			Time_Out--;
			if(Receive_Buffer_Full_Flag)
			{
				Receive_Buffer_Full_Flag = 0;
				Data_Check_OK = Crc_Caculate(&Receive_Buff,Receive_Date_Length);
				if(!Data_Check_OK)
				{
					if(Receive_Buff[0] == FUN_No4)
					{
						Send_Data(&Flash_Flag,1);
						flash_request = 1;
					}
				}
			}
			if(Time_Out==0)
			{
				return ;
			}
		}

		Time_Out = 100;
		while(!Flash_Ready_OK_Flag)
		{
			Time_Out--;
			if(Receive_Buffer_Full_Flag)
			{
				Receive_Buffer_Full_Flag = 0;
				Data_Check_OK = Crc_Caculate(&Receive_Buff,Receive_Date_Length);
				if(!Data_Check_OK)
				{
					if(Receive_Buff[0] == FUN_No9)
					{
						Flash_Ready_OK_Flag = Receive_Buff[2];
					}
				}
			}
			if(Time_Out==0)
			{
				return ;
			}
		}
		
		Trig_On;
		Send_Data(&Flash_Flag,1);
		
		Time_Out = 1000;
		while(Flash_OK_Flag)
		{
			Time_Out--;
			if(Receive_Buffer_Full_Flag)
			{
				Receive_Buffer_Full_Flag = 0;
				Data_Check_OK = Crc_Caculate(&Receive_Buff,Receive_Date_Length);
				if(!Data_Check_OK)
				{
					if(Receive_Buff[0] == FUN_No10)
					{
						Flash_OK_Flag = Receive_Buff[2];
					}
				}
			}
			if(Time_Out==0)
			{
				Trig_Off;
				return ;
			}
		}
		Trig_Off;
		Delay_ms(2);
	}
}
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
		Write_Num_TO_EEPROM(Flash_Times);
		if(Check_Write_EEPROM_Timeout == 20)
		{
			EEPROM_Write_Number_Error = 1;
			return;
		}
	}
	EEPROM_Write_Number_Error = 0;
}