#ifndef BOARD_COUNTER_H
#define BOARD_COUNTER_H




/*
#define SPI_MAG            SPI_0
#define SPI_CLK            (31)
#define SPI_MOSI           (29)
#define SPI_MISO           (02)
#define CS_MAG             (32+15)
*/

#define SPI_MAG            SPI_0
#define SPI_CLK            (4)
#define SPI_MOSI           (3)
#define SPI_MISO           (2)

/*magnétomètre*/
#define CS_MAG             (5)
#define INT1               (32+15)
#define INT2               (32+14)

/*Capteur d'angle 1*/
#define SPI_MA780        SPI_0
#define CS_ANGLE2          (6)
#define ND_ANGLE2          (9)
#define EN_ANGLE2          (31)
#define DV_ANGLE2          (32+2)
#define ASC_ANGLE2          (32+6)

/*Capteur d'angle 2*/

#define CS_ANGLE1          (7)
#define ND_ANGLE1          (32+3)
#define EN_ANGLE1          (30)
#define DV_ANGLE1          (32+1)
#define ASC_ANGLE1          (32+5)


/*Capteur de choc*/

#define IT_CHOC             (8)


/*Display*/
#define SPI_E_PAPER         SPI_1
#define RESET_DISPLAY        (10)
#define BSI_DISPLAY          (32+9)
#define DC_DISPLAY          (32+10)
#define BUZY_DISPLAY          (32+07)

#define SDI_DISPLAY          (32+12)
#define SCL_DISPLAY          (32+13)
#define CSB_DISPLAY          (14)


/*batterie*/

#define BAT_OK              (29)
#define V_BAT               NRF_SAADC_INPUT_AIN4    /*Pin 28*/



/*RS232*/
#define RS232_RX              (12)
#define RS232_TX              (26)



#endif


