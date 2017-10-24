#ifndef __UART_H
#define __UART_H

#include "SN8F5702.H"

#define DIRECTION_PIN									P02
#define UART_SEND											{P02 = 1;}
#define UART_RECEIVE									{P02 = 0;}

void Uart_Init(void);
void Uart_SendByte(uint8_t Data);
uint8_t Uart_ReceiveByte(void);

#endif