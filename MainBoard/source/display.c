#include "display.h"

void EPD_W21_Init(void);
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void driver_delay_us(unsigned int xus);
void lcd_chkstatus(void);
void EPD_W21_WriteDATA(unsigned char command);

void EPD_W21_WriteCMD(unsigned char command);
void EPD_display_init_Part(void);
void Part_lut_bw(void);
void increment_compteur(void);
void EPD_WhiteScreen_White(void);
void EPD_SetRAMValue_BaseMap( const unsigned char * datas);


unsigned char OldData1[500];
unsigned char OldData2[500];
unsigned char OldData3[500];
unsigned char OldData4[500];

unsigned char OldData_bat[500];
unsigned char OldData_unit[500];


unsigned char oldData[2024];


const unsigned char gImage_num_[24] = { 
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};



const unsigned char lut_w[] =
{
0x60	,0x01	,0x01	,0x00	,0x00	,0x01	,
0x80	,0x0f	,0x00	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,

};	


const unsigned char lut_b[] =
{
0x90	,0x01	,0x01	,0x00	,0x00	,0x01	,
0x40	,0x0f	,0x00	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,

};

const unsigned char gImage_0[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_1[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X06,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_2[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_3[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_4[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_5[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_6[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_7[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_8[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_9[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_B0[200] = { /*0X00,0X01,0X50,0X00,0X14,0X00,*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,
0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,
0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,
0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_B1[200] = {/* 0X00,0X01,0X50,0X00,0X14,0X00,*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,
0X00,0X00,0X00,0X02,0XF0,0X00,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF0,0X00,
0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF0,0X00,0X60,0X00,0X00,0X00,0X00,0X00,
0X00,0X02,0XF0,0X00,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_B2[200] = {/* 0X00,0X01,0X50,0X00,0X14,0X00,*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,
0X00,0X00,0X00,0X02,0XF3,0XC0,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF3,0XC0,
0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF3,0XC0,0X60,0X00,0X00,0X00,0X00,0X00,
0X00,0X02,0XF3,0XC0,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_B3[200] = { /*0X00,0X01,0X50,0X00,0X14,0X00,*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,0X00,0X00,
0X00,0X00,0X00,0X02,0XF3,0XCF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF3,0XCF,
0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0XF3,0XCF,0X60,0X00,0X00,0X00,0X00,0X00,
0X00,0X02,0XF3,0XCF,0X40,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X40,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
const unsigned char gImage_µl[200] = { /*0X00,0X01,0X50,0X00,0X14,0X00,*/
0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X06,0X36,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X36,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X36,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X06,0X36,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X36,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X06,0X37,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,
0X37,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XF0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X07,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};


//const unsigned char gImage_81[40] = { /* 0X00,0X01,0X10,0X00,0X10,0X00, */
//0X1F,0XF8,0X2F,0XF4,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X0F,0XF0,
//0X0F,0XF0,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X30,0X0C,0X2F,0XF4,0X1F,0XF8,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};


const unsigned char gImage_81[200] = { /* 0X00,0X01,0X50,0X00,0X14,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X80,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X60,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X7F,0XA0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

const unsigned char *niveau_bat[3]={
gImage_B0,
gImage_B1, 
gImage_B2
};

const unsigned char *chiffres[10]={
gImage_0,
gImage_1, 
gImage_2,
gImage_3,
gImage_4,
gImage_5,
gImage_6,
gImage_7,
gImage_8,
gImage_9  
};



 unsigned char mille=1;
  unsigned char cent=0;
  unsigned char dix=0;
  unsigned char unit=0;


uint32_t Display_open_SPI_1(void) {

    return (spi_open(SPI_E_PAPER, NRF_SPI_FREQ_1M, NRF_DRV_SPI_MODE_0,0xff,SDI_DISPLAY, SCL_DISPLAY, CSB_DISPLAY, true));

}




void initDisplay(void)
{

nrf_gpio_cfg_output(BSI_DISPLAY);
nrf_gpio_pin_clear(BSI_DISPLAY); 


nrf_gpio_cfg_output(SDI_DISPLAY);
nrf_gpio_cfg_output(SCL_DISPLAY);
nrf_gpio_cfg_output(CSB_DISPLAY);

nrf_gpio_cfg_output(DC_DISPLAY);
nrf_gpio_cfg_output(RESET_DISPLAY);


nrf_gpio_cfg_input(BUZY_DISPLAY,NRF_GPIO_PIN_NOPULL);

//Display_open_SPI_1();


EPD_init_OTP();

full_display(pic_display_white); //pic_white9

//EPD_WhiteScreen_White();
//	EPD_SetRAMValue_BaseMap(gImage_basemap);

//driver_delay_xms(3000);
	/*********partial display 0~9*********/
EPD_display_init_Part(); //EPD init Part
driver_delay_xms(10);	


//EPD_partial_display(0,0,gImage_fond,gImage_fond,gImage_fond,gImage_fond,128,80,0); //partial display 	
//driver_delay_xms(500);	
//EPD_partial_display(0,2,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],niveau_bat[0],gImage_µl,20,20,20*4,80,0); //partial display 	
EPD_partial_display(0,20,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],NULL,NULL,0,0,20*4,80,0); //partial display 
driver_delay_xms(500);	
//unit =1;
dix=2;
//cent=3;
//mille=4;
//EPD_partial_display(0,2,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],niveau_bat[3],gImage_µl,20,20,20*4,80,1); //partial display 	
//EPD_partial_display(0,2,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],niveau_bat[3],gImage_µl,20,20,20*4,80,1); //partial display 

EPD_partial_display(0,20,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],NULL,NULL,0,0,20*4,80,1); //partial display 


  	//EPD_partial_display(24,0,gImage_blanc,gImage_blanc,gImage_blanc,gImage_blanc,16*4,12,1); //partial display 

}

void EPD_Update(void)
{   
	//Refresh
	EPD_W21_WriteCMD(0x12);		//DISPLAY REFRESH 	
	driver_delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}

void EPD_WhiteScreen_White(void)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
	    EPD_W21_WriteDATA(0xFF); 
    }
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
			oldData[i]=0xFF; 
	  }
    EPD_Update();	    
}


//Partial refresh of background display, this function is necessary, please do not delete it!!!
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i;	
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0xFF);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
		  oldData[i]=datas[i]; 
   }	 
    EPD_Update();	    
}


/*************************EPD display init function******************************************************/
void EPD_init_OTP(void)
{	
		EPD_W21_Init();//Electronic paper IC reset
	
		EPD_W21_WriteCMD(0x00);  			
		EPD_W21_WriteDATA (0x5f);	// otp
	
		EPD_W21_WriteCMD(0x2A);			
		EPD_W21_WriteDATA(0x00); 
		EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteCMD(0x04);     		//power on	
  	lcd_chkstatus();//waiting for the electronic paper IC to release the idle signal
	  //Add the following code
		EPD_W21_WriteCMD(0x50);  		//Solve some black paper black border problems	
		EPD_W21_WriteDATA (0x97);	 
}


void EPD_W21_Init(void)
{
	EPD_W21_RST_0;		// Module reset
	driver_delay_xms(200);
	EPD_W21_RST_1;
	driver_delay_xms(200);
}


void driver_delay_xms(unsigned long t)
{
nrf_delay_ms(t);
}

void SPI_Delay(unsigned char xrate)
{
	unsigned char i;
	while(xrate)
	{
		for(i=0;i<EPD_W21_SPI_SPEED;i++);
		xrate--;
	}
}

void driver_delay_us(unsigned int xus)
{
	for(;xus>1;xus--);
}



void SPI_Write(unsigned char value)                                    
{                                                           




//	u8 tx[0] = {value};	
//  spi_transfer(SPI_E_PAPER, CSB_DISPLAY, true, tx, sizeof(tx), NULL,  0);



    unsigned char i;
	
	//SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
		//SPI_Delay(1);
        if(value & 0x80)
        	EPD_W21_MOSI_1;
        else
        	EPD_W21_MOSI_0;		
        value = (value << 1); 
		//SPI_Delay(1);
		//driver_delay_us(1);
        EPD_W21_CLK_1; 
       // SPI_Delay(1);
    }



}



void EPD_W21_WriteCMD(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}

void lcd_chkstatus(void)
{
	unsigned char busy;
 // driver_delay_xms(100);   
	do
	{
		EPD_W21_WriteCMD(0x71);
		busy = isEPD_W21_BUSY;
		busy =!(busy & 0x01);        
	}
	while(busy);   
	//driver_delay_xms(10);                       
}



/***************************full display function*************************************/
void full_display(void pic_display(void))
{

		
		pic_display(); //picture
	
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		EPD_W21_WriteCMD(0x02);
		lcd_chkstatus();
}



void pic_display_white(void)
{
	unsigned int i;
		EPD_W21_WriteCMD(0x10);
		for(i=0;i<1280;i++)	     
		{
				EPD_W21_WriteDATA(0x00);  
		}  
		driver_delay_xms(2);

		EPD_W21_WriteCMD(0x13);
		for(i=0;i<1280;i++)	     
		{
      EPD_W21_WriteDATA(0x00);   //noir : 00
		}  
		driver_delay_xms(2);	


}


void EPD_display_init_Part(void)
{
	EPD_W21_Init();
	EPD_W21_WriteCMD(0xD2);			
	EPD_W21_WriteDATA(0x3F); 
						 
	EPD_W21_WriteCMD(0x00);  			
	EPD_W21_WriteDATA (0x6F);  //from outside


	EPD_W21_WriteCMD(0x01);  			//power setting
	EPD_W21_WriteDATA (0x03);	    
	EPD_W21_WriteDATA (0x00);
	EPD_W21_WriteDATA (0x26);		
	EPD_W21_WriteDATA (0x26); 
	
	EPD_W21_WriteCMD(0x06);				
	EPD_W21_WriteDATA(0x3F);
	
	EPD_W21_WriteCMD(0x2A);			
	EPD_W21_WriteDATA(0x00); 
	EPD_W21_WriteDATA(0x00); 
	
	EPD_W21_WriteCMD(0x30);
	EPD_W21_WriteDATA(0x13); //50Hz
				
	EPD_W21_WriteCMD(0x50);			
	EPD_W21_WriteDATA(0xF2);

	EPD_W21_WriteCMD(0x60);			
	EPD_W21_WriteDATA(0x22);

	EPD_W21_WriteCMD(0x82);			
  EPD_W21_WriteDATA(0x00);//-0.1v

	EPD_W21_WriteCMD(0xe3);			
	EPD_W21_WriteDATA(0x33);

	Part_lut_bw();	
	
	EPD_W21_WriteCMD(0x04);     		//power on
  lcd_chkstatus();
}


void EPD_partial_display(u16 x_start,u16 y_start,
const unsigned char *new_data1,
const unsigned char *new_data2,
const unsigned char *new_data3,
const unsigned char *new_data4,
const unsigned char *new_data_bat,
const unsigned char *new_data_unit,
unsigned int PART_COLUMN_bat,
unsigned int PART_COLUMN_unit,


unsigned int PART_COLUMN_chiffre,
unsigned int PART_LINE_chiffre,
unsigned char mode) //partial display 

{
	unsigned int i,count,count_bat,count_unit;  
	unsigned int count1=0;
	unsigned int x_end,y_end;
	x_start=x_start;
	x_end=x_start+PART_LINE_chiffre-1; 
	
	y_start=y_start;
	y_end=y_start+PART_COLUMN_chiffre+PART_COLUMN_unit+PART_COLUMN_bat-1;

if(new_data1!=NULL)	count1++;
if(new_data2!=NULL)	count1++;
if(new_data3!=NULL)	count1++;
if(new_data4!=NULL)	count1++;


count=PART_COLUMN_chiffre*PART_LINE_chiffre/8/count1;
PART_COLUMN_chiffre=PART_COLUMN_chiffre;

count_bat = PART_COLUMN_bat*PART_LINE_chiffre/8;
count_unit = PART_COLUMN_unit*PART_LINE_chiffre/8;
	
	
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start);   //y-start    	
		EPD_W21_WriteDATA (y_end);  //y-end
		EPD_W21_WriteDATA (0x00);	

		EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming

 
	if(mode==0)
	for(i=0;i<count*4+count_bat*4+count_unit*4;i++)	     
	{
    EPD_W21_WriteDATA(0x00);    //noir : 00
		driver_delay_xms(2);  
	}
	else
	{



	if(OldData_bat != NULL)
		{
		for(i=0;i<count_bat;i++)	     
		{
		EPD_W21_WriteDATA(OldData_bat[i]);  
		driver_delay_xms(2);  
		} 
	}

	if(OldData1 != NULL)
		{
		for(i=0;i<count;i++)	     
		{
		EPD_W21_WriteDATA(OldData1[i]);  
		driver_delay_xms(2);  
		} 
	}
		if(OldData2 != NULL)
		{
	 for(i=0;i<count;i++)	     
	{
	 EPD_W21_WriteDATA(OldData2[i]);  
	driver_delay_xms(2);  
	} 
		}
			if(OldData3 != NULL)
		{
	 for(i=0;i<count;i++)	     
	{
	 EPD_W21_WriteDATA(OldData3[i]);  
	driver_delay_xms(2);  
	} 	
		}
			if(OldData4 != NULL)
		{
   for(i=0;i<count;i++)	     
	{
	 EPD_W21_WriteDATA(OldData4[i]);  
	driver_delay_xms(2);  
	}
		}

	if(OldData_unit != NULL)
		{
		for(i=0;i<count_unit;i++)	     
		{
		EPD_W21_WriteDATA(OldData_unit[i]);  
		driver_delay_xms(2);  
		} 
	}



}
	EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
	if(mode!=2) //new  datas
	{

			if(new_data_bat != NULL)
		{
		for(i=0;i<count_bat;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data_bat[i]);  
		 OldData_bat[i]=~new_data_bat[i];
		 driver_delay_xms(2);  
	 }
	}


			if(new_data1 != NULL)
		{
		for(i=0;i<count;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data1[i]);  
		 OldData1[i]=~new_data1[i];
		 driver_delay_xms(2);  
	 }
	}
			if(new_data2 != NULL)
		{
	 	for(i=0;i<count;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data2[i]);  
		 OldData2[i]=~new_data2[i];
		 driver_delay_xms(2);  
	 }
		}
					if(new_data3 != NULL)
		{

	 	for(i=0;i<count;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data3[i]);  
		 OldData3[i]=~new_data3[i];
		 driver_delay_xms(2);  
	 }
		}
					if(new_data4 != NULL)
		{

   	for(i=0;i<count;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data4[i]);  
		 OldData4[i]=~new_data4[i];
		 driver_delay_xms(2);  
	 }
   
		}

			if(new_data_unit != NULL)
		{
		for(i=0;i<count_unit;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data_unit[i]);  
		 OldData_unit[i]=~new_data_unit[i];
		 driver_delay_xms(2);  
	 }
	}

   
  }
  else  //white
  {
		for(i=0;i<count*4;i++)	     
		{
		 EPD_W21_WriteDATA(0xff);  
			driver_delay_xms(2);  
		}		
	}		
    	
		EPD_W21_WriteCMD(0x12);		 //DISPLAY REFRESH 		             
		driver_delay_xms(10);     //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
	 
}

void Part_lut_bw(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x23);
	for(count=0;count<42;count++)	     
	{EPD_W21_WriteDATA(lut_w[count]);}    
	
	EPD_W21_WriteCMD(0x24);
	for(count=0;count<42;count++)	     
	{EPD_W21_WriteDATA(lut_b[count]);}          
}

void increment_compteur(void)
{
 unit++;

  if(unit >=10)
  {
    unit=0;
    dix++;
    if(dix >=10)
    {
      dix=0;
      cent++;
      if(cent>=10)
      {
        cent=0;
        mille++;
        if(mille>=10)
        {
          mille=0;
        }
      }
    }
  }    
  }

void affichage_display(float f)
{
u8 mille = 0;
u8 cent = 0;
u8 dix = 0;
u8 unit = 0;

while (f >= 1000)
{
mille++;
f=f-1000;
}

while (f >= 100)
{
cent++;
f=f-100;
}

while (f >= 10)
{
dix++;
f=f-10;
}

while (f >= 1)
{
unit++;
f=f-1;
}
 //	EPD_partial_display(0,0,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],16*4,12,0); //partial display 

}



void testDisplay(float f)
{
 	//EPD_partial_display(0,0,chiffres[unit],chiffres[dix],chiffres[cent],chiffres[mille],32*4,32,1); //partial display 
 increment_compteur();
}
