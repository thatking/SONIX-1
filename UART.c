#include "UART.h"
#include "protocol.h"

uint8_t Recive_Buff[10];
uint8_t Recive_Count = 0;
uint8_t Head_Flag = 0;
uint8_t Recive_Buffer_Full_Flag = 0;
uint8_t Recevie_Date_Length = 0;

extern uint8_t Analysis_Lock;

void Uart_Init(void)
{
	/* IO Initialize */
	P05 = 1;
	DIRECTION_PIN = 1;   /* transmission */
	P0M |= 0x24;  /* P0.5-->TX:OUT,DIRECTION_PIN P0.2:OUT */
	P0M &= ~0x40;  /* P0.6-->RX:IN */
	P0OC &= ~0x03;  /* P0.5 P0.6 OD disable */
	P0UR &= ~0x24;  /* P0.5,P0.2 Pull_up disable */
	P0UR |= 0x40;  /* P0.6 Pull_up able */
	
	PCON |= 0x80;
	S0CON = 0x50;  /* Uart model 1, enable recvied, clean flag*/
	S0CON2 = 0x80;  /* baud rate controlled by S0RELH,S0RELL */
	S0RELH = 0x03;  /* Baud rate 128000 */
	S0RELL = 0xFC;
  IEN0 |= 0x10;   /* enable uart Interrupt */
}

void Uart_SendByte(uint8_t Data)
{
 UART_SEND;
 IEN0 &= ~0x10;  /* disable uart Interrupt */
 S0BUF = Data;
 while(!(S0CON & 0x02));
 //S0BUF = Data;
 S0CON &= ~0x02;
 IEN0 |= 0x10;  /* enable uart Interrupt */
 UART_RECEIVE;
}

void Uart_SendStr(uint8_t *str)
{
	UART_SEND;
  IEN0 &= ~0x10;  /* disable uart Interrupt */
	while(*str != '\0')
	{
		S0BUF = *str++;
    while(!(S0CON & 0x02));
    S0CON &= ~0x02;
	}
	IEN0 |= 0x10;  /* enable uart Interrupt */
  UART_RECEIVE;
}

uint8_t Uart_ReceiveByte(void)
{
 return ((uint8_t)S0BUF);
}

void UartInterrupt(void) interrupt ISRUart
{
	if(RI0 == 1)
	{
		RI0 = 0;			
		if(!Head_Flag)
		{
			if(S0BUF == BUS_HEADER)
			{
				Head_Flag = 1;
			}
		}else{
			if(S0BUF != BUS_END)
			{
				Recive_Buffer_Full_Flag = 0;
				//if(!Analysis_Lock)
			//	{	
					if(Recive_Count < 10)
				  {
					  Recive_Buff[Recive_Count] = S0BUF;		
					  Recive_Count ++;	
				  }else{
					  Head_Flag = 0;
					  Recive_Count = 0;
				  }
			//	}else{
				//	Head_Flag = 0;
				//	Recive_Count = 0;
				
			}else{
				 Recevie_Date_Length = Recive_Count;		 
				 Head_Flag = 0;
				 Recive_Count = 0;
				 Recive_Buffer_Full_Flag = 1;
			}	 
		}
	}
}	