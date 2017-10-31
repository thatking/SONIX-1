#ifndef __FLASH_CONTROL_H
#define __FLASH_CONTROL_H

#include "SN8F5702.h"

#define Trig_On							          {P07 = 1;}
#define Trig_Off							        {P07 = 0;}

#define Full_Charge_LED_On	          {P01 = 1;}
#define Full_Charge_LED_Off						{P01 = 0;}

#define Flash_Times_Level1            30000
#define Flash_Times_Level2            40000
#define Flash_Times_Level3            50000
#define Flash_Times_Level4            60000
#define Flash_Times_Level5            70000
#define Flash_Times_Level6            80000
#define Flash_Times_Level7            90000
#define Flash_Times_Level8            100000

#define Flash_Times_Level_9					  9
#define Flash_Times_Level_8					  8
#define Flash_Times_Level_7					  7
#define Flash_Times_Level_6					  6
#define Flash_Times_Level_5					  5
#define Flash_Times_Level_4					  4
#define Flash_Times_Level_3					  3
#define Flash_Times_Level_2					  2
#define Flash_Times_Level_1					  1

void Flash_IO_Init(void);
void Flash_Control(uint8_t flash_times);


#endif
