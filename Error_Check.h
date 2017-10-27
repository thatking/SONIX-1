#ifndef __ERROR_CHECK_H
#define __ERROR_CHECK_H

#include "SN8F5702.H"

#define FAN_OPEN_ERROR_THR                409  /* fan open: 0v*/
#define FAN_SHORT_ERROR_THR               4000 /* fan short: 5v */

#define CARTRIDGE_ERROR_THR               400  /* cartridge open: 0v */         
#define CARTRIDGE_TYPE_1_H                2457 /* One Lamp: 2.5v--3.5v */
#define CARTRIDGE_TYPE_1_L                2048 
#define CARTRIDGE_TYPE_2                  3686 /* two lamp: 4.5v */

void Fan_Error_Check(void);
void Cartridge_Error_Check(void);
void Cartridge_Type_Check(void);
void Error_Check(void);


#endif