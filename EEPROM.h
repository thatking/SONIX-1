/**
  ******************************************************************************
  * @file    EEPROM.h
  * @author  Captain.
  * @version V1.1.0
  * @date    2017-6-22
  * @brief   define EEPROM Functions.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 YUJIN</center></h2>
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "SN8F5702.H"

/*
********************************************************************************
*                                PORT DEFINE
********************************************************************************
*/
//#define EEPROM_EEROR_SAK_TIMEOUT        1
//#define EEPROM_EEROR_NoSAK_TIMEOUT      2

#define EEPORM_UNIO_PORT                P2
#define EEPROM_UNIO_PIN                 P20

/*
********************************************************************************
*                         EEPORM  DATA STORE ADDR DEFINE
********************************************************************************
*/
#define EEPROM_DEVICE_ADDR              0xA0
#define DATA_ADDR                       0x0000
#define DATA_ADDR_H                     0x00
#define DATA_ADDR_L                     0x00

/*
********************************************************************************
*                              EEPORM  WAIT TIME
********************************************************************************
*/
#define EEPROM_WAIT                     0x14

/*
********************************************************************************
*                              EEPORM  STARTHEAD
********************************************************************************
*/
#define EEPROM_STARTHEADER              0x55

/*
********************************************************************************
*                              EEPORM  COMMAND
********************************************************************************
*/
#define CMD_READ                        0x03
#define CMD_CRRD                        0x06
#define CMD_WRITE                       0x6C
#define CMD_WREN                        0x96
#define CMD_WRDI                        0x91
#define CMD_RDSR                        0x05
#define CMD_WRSR                        0x6E
#define CMD_ERAL                        0x6D
#define CMD_SETAL                       0x67

#define SET_IO_LOW(p)                   {p=0;}
#define SET_IO_HIGH(p)                  {p=1;}

#define EEPROM_MAK()										{ SET_IO_LOW(EEPROM_UNIO_PIN);        /* SCIO Output 0*/\
																					Delay_10us();\
																					Delay_10us();\
																					Delay_10us();\
																					SET_IO_HIGH(EEPROM_UNIO_PIN);        /* SCIO Output 1*/\
																					Delay_10us();\
																					Delay_10us();\
																					Delay_10us();}
#define EEPROM_NoMAK()									{ SET_IO_HIGH(EEPROM_UNIO_PIN);        /* SCIO Output 1*/\
																					Delay_10us();\
																					Delay_10us();\
																					Delay_10us();\
																					SET_IO_LOW(EEPROM_UNIO_PIN);        /* SCIO Output 0*/\
																					Delay_10us();\
																					Delay_10us();\
																					Delay_10us();}
#define EEPROM_StartHeader()            { SET_IO_HIGH(EEPROM_UNIO_PIN);\
																					Delay_N_10us(60);\
																					SET_IO_LOW(EEPROM_UNIO_PIN);\
																					Delay_5us();\
																					Delay_10us();\
																					EEPROM_Write_Byte(EEPROM_STARTHEADER);\
																					EEPROM_MAK();\
																					EEPROM_NoSAK();}

/*
********************************************************************************
*                                FUNCTIONS
********************************************************************************
*/

//void EEPROM_MAK(void) ;
//void EEPROM_NoMAK(void);
void EEPROM_SAK(void);
void EEPROM_NoSAK(void);
void EEPROM_Write_Byte(uint8_t write_data);
uint8_t EEPROM_Read_Byte(void);
//void EEPROM_StartHeader(void);
//void EEPROM_Read_Data(uint8_t *data_arry, uint16_t read_addr, uint8_t read_num);
//void EEPROM_Write_Data(uint8_t *data_arry, uint16_t write_addr, uint8_t write_num);
void EEPROM_Write_CMD(uint8_t cmd);
//uint8_t EEPROM_Read_SR(void);
//void EEPROM_Write_SR(uint8_t srdata);
void EEPROM_IO_Init(void);
void Write_Num_TO_EEPROM(uint32_t flash_count);
uint32_t Read_Num_From_EEPROM(void);

#endif /* __EEPROM_H */


/************************ (C) COPYRIGHT YUJIN *****END OF FILE*****************/
