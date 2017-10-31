#include "key.h"
#include "Flash_Control.h"
#include "Error_Check.h"
#include "protocol.h"

uint8_t Key_Trig = 0;
uint8_t Key_Count = 0;
uint8_t Key_Read = 0;
uint8_t Standard_Flash_Lock = 0;
uint8_t Key_Delay_Count = 0;
uint8_t Key_Push = 0;
uint8_t Full_Charge_Flag = 0;
uint8_t Low_Lamp;

extern uint8_t Mode_Type ;
extern uint8_t Flash_Times_Level;
extern uint8_t Low_Lamp ;

extern uint8_t Lock_Flag;
extern uint8_t Error_Flag;


void Key_IO_Init(void)
{
	P1M &= ~0x01;   /* P10:Touch Input */ 
	P0M &= ~0x01;   /* P00:Flash SW Input */
	P1UR &= ~0x01;   /* P10:Disable Pull up */
	P0UR |= 0x01;   /* P00:enable Pull up */
}


void Key_Scan(void)
{
	uint8_t temp_p1 = P1;
	temp_p1 <<= 1;
	Key_Read = (P0&0x01) | (temp_p1 & 0x02) ^ 0xFF;  /* not */
	Key_Trig = Key_Read & (Key_Read ^ Key_Count);
	Key_Count = Key_Read;
	if((Mode_Type == Standard_Mode) || (Mode_Type == Standard_Multi_Mode))
	{
		if(!(Key_Count & TOUCH_PIN))
		{
			Standard_Flash_Lock = 1;
		}else{
			if(!(Key_Count & FLASH_SW_PIN))
			{
				Standard_Flash_Lock = 0;
			}			
		}
	}
}


void Key_Process(void)
{
	if(!Lock_Flag)
	{
		if(Key_Count & FLASH_SW_PIN)
		{
			if(Key_Trig & FLASH_SW_PIN)
			{
				Key_Push = 1;
			}
			if(Key_Push == 1)
			{
				Key_Delay_Count ++;
				if(Key_Delay_Count == 200)
				{
					Key_Push = 0;
					Key_Delay_Count = 0;
					switch(Mode_Type){
						case Auto_Mode : Mode_Type = Auto_Multi_Mode;break;
						case Auto_Multi_Mode : Mode_Type = Auto_Mode;break;
						case Standard_Mode : Mode_Type = Standard_Multi_Mode;break;
						case Standard_Multi_Mode : Mode_Type = Standard_Mode;break;
						default : break;
				  }
			  }
			}
		}else{
			Key_Push = 0;
			Key_Delay_Count = 0;
		}
		
		if((!(Error_Flag)) || (!(Full_Charge_Flag)) || (!(Low_Lamp))) 
		{
			Key_Scan();
			switch(Mode_Type){
			case Auto_Mode : Auto_Flash();break;
			case Auto_Multi_Mode : Auto_Multi_Flash();break;
			case Standard_Mode : Standard_Flash();break;
			case Standard_Multi_Mode : Standard_Multi_Flash();break;
			default : break;			 
			}
		}
	}
}


void Auto_Flash(void)
{
  if(Key_Count & TOUCH_PIN)
	{
	 Flash_Control(1);
  }
}

void Auto_Multi_Flash(void)
{
  if(Key_Count & TOUCH_PIN)
	{
		Flash_Control(3);
	}
}

void Standard_Flash(void)
{
	if(!Standard_Flash_Lock)
	{
		if(Key_Count & FLASH_SW_PIN)
		{
			Standard_Flash_Lock = 1;
			Flash_Control(1);
		}
	}
}


void Standard_Multi_Flash(void)
{
	if(!Standard_Flash_Lock)
	{
		if(Key_Count & FLASH_SW_PIN)
		{
			Standard_Flash_Lock = 1;
			Flash_Control(3);
		}
	}
}
