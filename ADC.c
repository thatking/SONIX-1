/**
  ******************************************************************************
  * @file    ADC.c
  * @author  Captain.
  * @version V1.1.0
  * @date    2017-6-22
  * @brief   This file implement functions that in ADC.h define.
   *****************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 YUJIN</center></h2>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ADC.h"
//#include "delay.h"
//#include "stdio.h"

/* Public Functions ----------------------------------------------------------*/

/*
********************************************************************************
*                                       ADC INITIALIZATION FUNCTIONS
*
* Description: This function is called by Init_Fun() in GPIO_Config.h at the beginning in main() .
*
* Arguments  : none
*
* Note(s)    : none.
********************************************************************************
*/
void ADC_Init_Fun(void)
{
  ADM = 0x00;  //stop and disable adc;
	P1M &= ~0x16;  //P11,P12,P14 input;
  //P2M &= ~0x01;  //P20 input;
	P1UR &= ~0x16;  //P11,P12,P14 disable pull up;
	//P2UR &= ~0x01;  //P20 disable pull up;
	P1CON |= 0x16;  //disable P11,P12,P14 schmitt trigger
	//P2CON |= 0x01; //disable P20 schmitt trigger
	VREFH = 0x07;  //Vref = VDD = 5V;
	ADR = 0x40;  //Enable AIN channel, Fadc = Fosc/8 = 4MHz; T = 16us
}

/*
********************************************************************************
*                                       READ ONE ADC CHANNEL VALUE FUNCTIONS
*
* Description: This function read one ADC channel value,return the 16 Bit converter value.
*
* Arguments  : wangt convert ADC channel
*
* Return  : Return the convert value of 16 Bit for the channel
*
* Note(s)    : none.
********************************************************************************
*/
uint16_t ADC_Read_Channel_Fun(uint8_t channel)
{
  uint16_t readdata,read_arry[6];  
  uint8_t i,j;
  ADM  = channel;    /* Clean Flag, Select Channel  */
  ADM |= 0x80;    /* Enable ADC */
  //Delay_us(10);   /* Must Need Delay 7us More Than */
  for(i=0;i<5;i++)
  {   
		ADM |= 0x40;    /* Start Conversion */
    while(!(ADM & 0x20));   /* Wait Conversion Complete ,Convert 5 Times*/
    read_arry[i+1] = (uint16_t)ADB;     /* Read Data Convertsion to 16 Bit*/
    read_arry[i+1] = (read_arry[i+1] << 4) + (uint16_t)(ADR & 0x0F);
    ADM &= ~0x20;  /* Clear Complete Flag */
  }
  ADM &= ~0x80;    /* Disable ADC */
  
/* Filter Funtion**************************************************************/
  for(i=1;i<6;i++)  /* Insert sort */
  {
    read_arry[0] = read_arry[i];
    for(j=i-1; read_arry[0]<read_arry[j]; j--)
    {
        read_arry[j+1] = read_arry[j];
    }
    read_arry[j+1] = read_arry[0];
  }
  readdata = read_arry[3]; /*  Midle Data to Retrun */
/******************************************************************************/
  return readdata;
}


/************************ (C) COPYRIGHT YUJIN *****END OF FILE*****************/


