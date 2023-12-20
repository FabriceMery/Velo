#ifndef MA780_H
#define MA780_H

#include "Globale.h"





#define  Z_7_0                  0x0
#define  Z_15_8                 0x1
#define  BCT_7_0                0x2
#define  ETX_ETY                0x3
#define  TCYC_7_0               0x4
#define  TCYC_15_8              0x5
#define  TACT_7_0               0x7
#define  THHR_7_0               0x8
#define  RD                     0x9
#define  REF_7_0                0xA
#define  ASCR_ASC_AUTACT        0xB
#define  FW                     0xE
#define  MULTI_1_0              0x16
#define  ERRPAR_ERRMEM_ERRNVM   0x1A

typedef enum
{
  WRITE,
  READ
} READ_WRITE;
  

u8 u8_read_write_TCYC_LOW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
u8 u8_read_write_TCYC_HIGH(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
u8 u8_read_write_Z_LOW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
u8 u8_read_write_Z_HIGH(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
 float f_readAngle( uint32_t SEL_SS_PINOUT);
u8 u8_read_write_FW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
u8 u8_read_write_RD(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
 void SensAngle(bool sens,uint32_t SEL_SS_PINOUT );


#endif
