#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "SN8F5702.h"

#define BUS_HEADER    							0xA5
#define BUS_END											0x5A

/* Master Request -------------------------------------------------------------*/
#define FUN_No1							        0x01  /* get flash times */
#define FUN_No2							        0x02  /* get flash times level */
#define FUN_No3							        0x03  /* get skin color level */
#define FUN_No4							        0x04  /* get Flash Flag */
#define FUN_No5							        0x05  /* get Flash OK Flag */
#define FUN_No6							        0x06  /* get ERROR flag */

/* Master Send Data -----------------------------------------------------------*/
#define FUN_No7											0x07  /* Full Charge flag */
#define FUN_No8											0x08  /* Mode Type */
#define FUN_No9											0x09  /* Flash Ready OK Flag */
#define FUN_No10										0x0A  /* Flash Level */

#define CRC_8										    0x31  /* CRC_CCITT */

#endif
