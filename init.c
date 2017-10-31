#include "init.h"
#include "Error_Check.h"
//#include ""

extern uint32_t Flash_Times;
extern uint8_t Lamp_Type;
extern uint8_t Flash_Times_Level;
extern uint8_t Low_Lamp;

void Init_Fun(void)
{
	UART_SEND;
	Flash_IO_Init();
	Delay_Init();
	Uart_Init();
	ADC_Init_Fun();	
	EEPROM_IO_Init();	
	Key_IO_Init();
	Cartridge_Type_Check();
	UART_RECEIVE;
  Flash_Times = Read_Num_From_EEPROM();
  if(Flash_Times >= Flash_Times_Level8)
	{
		Flash_Times_Level = Flash_Times_Level_9;
		Low_Lamp = 1;
	}else{
		Low_Lamp = 0;
		if(Flash_Times >= Flash_Times_Level7)
		{
			Flash_Times_Level = Flash_Times_Level_8;
		}else{
			if(Flash_Times >= Flash_Times_Level6)
			{
				Flash_Times_Level = Flash_Times_Level_7;
			}else{
				if(Flash_Times >= Flash_Times_Level5)
				{
					Flash_Times_Level = Flash_Times_Level_6;
				}else{
					if(Flash_Times >= Flash_Times_Level4)
					{
						Flash_Times_Level = Flash_Times_Level_5;
					}else{
						if(Flash_Times >= Flash_Times_Level3)
						{
							Flash_Times_Level = Flash_Times_Level_4;
						}else{
							if(Flash_Times >= Flash_Times_Level2)
							{
								Flash_Times_Level = Flash_Times_Level_3;
							}else{
								if(Flash_Times >= Flash_Times_Level1)
								{
									Flash_Times_Level = Flash_Times_Level_2;
								}else{
									Flash_Times_Level = Flash_Times_Level_1;
								}
							}
						}
					}
				}
			}
		}
	}		
}
