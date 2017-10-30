#include "main.h"
#include "SN8F5702.H"
#include "delay.h"
#include "UART.h"
#include "protocol.h"
#include "ADC.h"
#include "EEPROM.h"

extern uint8_t Recive_Buffer_Full_Flag;
extern uint8_t Recive_Buff[10];
extern uint8_t Recevie_Date_Length;

void main(void)
{
	WDTR = 0x5A;
	Init_Fun();
	IEN0 |= 0x80;
	while(1)
	{	
		Error_Check();
		Analysis_Request();
		Key_Process();
	}
}
