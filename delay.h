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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "SN8F5702.H"

//#define Delay_us()             	
		


/*
********************************************************************************
*                               DELAY FUNCTION
********************************************************************************
*/

void Delay_5us(void);
void Delay_N_5us(uint8_t N);
void Delay_N_10us(uint8_t N);
void Delay_10us(void);
void Delay_ms(uint16_t N);
void Delay_Init(void);

#endif /* __DELAY_H */


/************************ (C) COPYRIGHT YUJIN *****END OF FILE*****************/