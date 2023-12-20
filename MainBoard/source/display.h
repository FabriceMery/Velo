
#ifndef DISPLAY_H
#define DISPLAY_H

#include "Globale.h"


#define EPD_WIDTH   80
#define EPD_HEIGHT  128
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  

void initDisplay(void);
void EPD_init_OTP(void);
void driver_delay_xms(unsigned long t);
void full_display(void pic_display(void));
void pic_display_white(void);
void EPD_partial_display(u16 x_start,u16 y_start,
const unsigned char *new_data1,
const unsigned char *new_data2,
const unsigned char *new_data3,
const unsigned char *new_data4,
const unsigned char *new_data_bat,
const unsigned char *new_data_unit,
unsigned int PART_COLUMN_bat,
unsigned int PART_COLUMN_unit,


unsigned int PART_COLUMN_chifre,
unsigned int PART_LINE_chifre,
unsigned char mode) ;



void testDisplay(float f);

void affichage_display(float f);



#define EPD_W21_SPI_SPEED 0x01



#define EPD_W21_MOSI_0	nrf_gpio_pin_clear(SDI_DISPLAY)
#define EPD_W21_MOSI_1	nrf_gpio_pin_set(SDI_DISPLAY)

#define EPD_W21_CLK_0	nrf_gpio_pin_clear( SCL_DISPLAY )
#define EPD_W21_CLK_1	nrf_gpio_pin_set(SCL_DISPLAY)

#define EPD_W21_CS_0	nrf_gpio_pin_clear(CSB_DISPLAY)
#define EPD_W21_CS_1	nrf_gpio_pin_set(CSB_DISPLAY)

#define EPD_W21_DC_0	nrf_gpio_pin_clear(DC_DISPLAY)
#define EPD_W21_DC_1	nrf_gpio_pin_set(DC_DISPLAY)

#define EPD_W21_RST_0	nrf_gpio_pin_clear(RESET_DISPLAY)
#define EPD_W21_RST_1	nrf_gpio_pin_set(RESET_DISPLAY)

#define isEPD_W21_BUSY  nrf_gpio_pin_read(BUZY_DISPLAY) // for solomen solutions



#endif
