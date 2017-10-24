#include "skin_color_check.h"
#include "ADC.h"

uint8_t Skin_Tpye = 2;

void Skin_Color_Check(void)
{
	uint16_t readdata;
	readdata = ADC_Read_Channel_Fun(ADC_RGB_CHANNEL);
	if((readdata < COLOR_TPYE_1_H) && (readdata > COLOR_TPYE_1_L))
	{
		Skin_Tpye = 1;
	}
	if((readdata < COLOR_TPYE_2_H) && (readdata > COLOR_TPYE_2_L))
	{
		Skin_Tpye = 2;
	}
	if((readdata < COLOR_TPYE_3_H) && (readdata > COLOR_TPYE_3_L))
	{
		Skin_Tpye = 3;
	}
}