/**
  ******************************************************************************
  * @file    ADC.h
  * @author  Captain.
  * @version V1.1.0
  * @date    2017-6-22
  * @brief   define ADC Pin, PORT, Channel and Functions.
   *****************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 YUJIN</center></h2>
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "SN8F5702.h"

/*
********************************************************************************
*                               ADC  Channel
********************************************************************************
*/
#define ADC_CARTRIDG_PIN               P11  /* Main Fan Error Pin */
#define ADC_FAN_PIN                    P12  /* Cartridg And Probe Fan Error Pin */
#define ADC_RGB_PIN                    P14  /* Hight Voltage Sample Pin */

#define ADC_CARTRIDG_CHANNEL           ADC1_CHANNEL_1 /* Cartridg And Probe Fan Error Channel */
#define ADC_FAN_CHANNEL                ADC1_CHANNEL_2 /* Fan error Channel */
#define ADC_RGB_CHANNEL								 ADC1_CHANNEL_4  /* RGB sensor Channel */

#define ADC1_CHANNEL_1								 0x01
#define ADC1_CHANNEL_2                 0x02
#define ADC1_CHANNEL_4                 0x04
/*
********************************************************************************
*                               ADC  FUNCTIONS
********************************************************************************
*/
void ADC_Init_Fun(void);
uint16_t ADC_Read_Channel_Fun(uint8_t channel);

#endif /* __ADC_H */


/************************ (C) COPYRIGHT YUJIN *****END OF FILE*****************/
