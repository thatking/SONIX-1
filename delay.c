/**
  ******************************************************************************
  * @file    delay.c
  * @author  Captain.
  * @version V1.1.0
  * @date    2017-6-22
  * @brief   This file implement delay ms and delay us functions. 
   *****************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 YUJIN</center></h2>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/* Public Functions ----------------------------------------------------------*/

/*
********************************************************************************
*                                       DELAY US FUNCTIONS
*
* Description: This function Delay N us.
*
* Arguments  : Number of Delay times.
*
* Note(s)    : none.
********************************************************************************
*/
void Delay_us(u16 nus)
{  
  while(nus--)
	{
		TH0 = 0xFF;     /* 1 us */
		TL0 = 0xE0;
		TR0 = 1;  //enable timer;
    while(!(TF0));
	}
	TR0 = 0;  //disable timer;
}

/*
********************************************************************************
*                                       DELAY MS FUNCTIONS
*
* Description: This function Delay N ms.
*
* Arguments  : Number of Delay times.
*
* Note(s)    : none.
********************************************************************************
*/
void Delay_ms(uint16_t N)
{
  while(N--)
  {
    TH0 = 0x83;     /* 1 ms */
		TL0 = 0x00;
		TR0 = 1;  //enable timer;
    while(!(TF0));
  }
	TR0 = 0;  //disable timer;
}

void Delay_Init(void)
{
	//IEN0  //disable Interrupt
	TF0 = 0;   //clean flag;
	TR0 = 0;  //disable timer;
	TCON0 |= 0x70; //Ft0 = 32MHz;
	TH0 = 0x00;
	TL0 = 0x00;
	TMOD |= 0x05;  //Ft0 = Fosc, 16 Bit up;
}

/************************ (C) COPYRIGHT YUJIN *****END OF FILE*****************/