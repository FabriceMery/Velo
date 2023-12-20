#include "MA780.h"


 static u8 u8_readRegister( u8 addressToRead,u8*var_rx,uint32_t SEL_SS_PINOUT );
 static  u8 u8_writeRegister( u8 addressToWrite, u8 message,uint32_t SEL_SS_PINOUT );
 static u8 u8_read_write_MAG780(u8 u8_registre,u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT);
static u32 u32_spi_master_tx_rx(
	uint16_t transfer_size, 
	const uint8_t *tx_data, 
	uint8_t *rx_data,
	uint32_t SEL_SS_PINOUT,
	uint8_t etat
	);


uint32_t MA780_open_SPI_1(void) {

    return (spi_open(SPI_MA780, NRF_SPI_FREQ_8M, NRF_DRV_SPI_MODE_0,SPI_MISO,SPI_MOSI, SPI_CLK, CS_ANGLE1, true));

}

void MA780_close_SPI_1(void)
{
spi_close(SPI_MA780);
}

 static u8 u8_readRegister( u8 addressToRead,u8*var_rx,uint32_t SEL_SS_PINOUT )
{
	u8 rx[2] = {0,0};
	u8 tx[0] = { addressToRead | 0x40};	
  spi_transfer(SPI_MA780, SEL_SS_PINOUT, true, tx, sizeof(tx), rx,  sizeof(rx));
 
  return(rx[1]);
                                                                                                                                                                                                                        	return var_rx[1] ;
}	

 static u8 u8_writeRegister( u8 addressToWrite, u8 message,uint32_t SEL_SS_PINOUT )
{
	u8 rx[2] = {0,0};
 	u8 tx[2] = {addressToWrite | 0x80,message};

  spi_transfer(SPI_MA780, SEL_SS_PINOUT, true, tx, sizeof(tx), rx,  sizeof(rx));
  return(rx[1]);  
}	



static u8 u8_read_write_MAG780(u8 u8_registre,u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT )
{
  u8 u8_status = true;  
  u8 u8_value = 0;
  u8 var_rx[2] = {0,0};
  if(ewrite == READ)
  {
    u8_value = u8_readRegister(u8_registre,var_rx,SEL_SS_PINOUT );  
  }
  else
  {
    u8_value =  u8_writeRegister( u8_registre,u8_valueToWrite,SEL_SS_PINOUT );
  }
    
  return(u8_value);  
}



u8 u8_read_write_TCYC_LOW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(TCYC_7_0,u8_valueToWrite,ewrite,SEL_SS_PINOUT));  
}


u8 u8_read_write_TCYC_HIGH(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(TCYC_15_8,u8_valueToWrite,ewrite,SEL_SS_PINOUT));  
}


u8 u8_read_write_Z_LOW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(Z_7_0,u8_valueToWrite,ewrite, SEL_SS_PINOUT));  
}

u8 u8_read_write_Z_HIGH(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(Z_15_8,u8_valueToWrite,ewrite,SEL_SS_PINOUT));  
}


u8 u8_read_write_FW(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(FW,u8_valueToWrite,ewrite,SEL_SS_PINOUT));  
}

u8 u8_read_write_RD(u8 u8_valueToWrite,READ_WRITE ewrite,uint32_t SEL_SS_PINOUT)
{
  return(u8_read_write_MAG780(RD,u8_valueToWrite,ewrite,SEL_SS_PINOUT));  
}


 float f_readAngle( uint32_t SEL_SS_PINOUT)
{
  float value = 0;
  u8 rx[2] = {0,0};
  u8 tx[2] = {0,0};

  spi_transfer(SPI_MA780, SEL_SS_PINOUT, true, tx, sizeof(tx), rx,  sizeof(rx));


  value = (rx[0]<<8) +  rx[1]; 

  value = value * 359.995;
  value = value / 65535;

return(value);
}


 void SensAngle(bool sens,uint32_t SEL_SS_PINOUT )
 {
if(sens==0)
{
  u8_read_write_RD(0x00,WRITE, SEL_SS_PINOUT);
}
  else
  {
u8_read_write_RD(0x80,WRITE, SEL_SS_PINOUT);
  }
 }