#include "mlx90393.h"

  enum mlx90393_gain _gain;
  enum mlx90393_resolution _res_x, _res_y, _res_z;
  enum mlx90393_filter _dig_filt;
  enum mlx90393_oversampling _osr;

  int32_t _sensorID = 90393;


void tempo( unsigned int t);


/*!
 *    @brief  Sets up the hardware and initializes hardware SPI
 *    @param  cs_pin The arduino pin # connected to chip select
 *    @param  theSPI The SPI object to be used for SPI connections.
 *    @return True if initialization was successful, otherwise false.
 */
uint32_t MLX90393_open_SPI(void) {

   return (spi_open(SPI_MAG, NRF_SPI_FREQ_8M, NRF_DRV_SPI_MODE_3,SPI_MISO,SPI_MOSI, SPI_CLK, CS_MAG, true));

}

void MLX90393_close_SPI(void)
{
spi_close(SPI_MAG);
}

bool init_MLX90393(void) {


  if (!MLX90393_exitMode()){
   NRF_LOG_DEBUG("MLX90393_exitMode FALSE");
   return false;
  }


  if (!MLX90393_reset()) {
      NRF_LOG_DEBUG("MLX90393_reset FALSE");
      return false;
  }
   tempo( 100);
  //nrf_delay_ms(100);
//}

  /* Set gain and sensor config. */
  if (!MLX90393_setGain(MLX90393_GAIN_1X)) {
     NRF_LOG_DEBUG("MLX90393_setGain FALSE");
    return false;
  }



  /* Set resolution. */
  if (!MLX90393_setResolution(MLX90393_X, MLX90393_RES_16)) {
    return false;
  }
  if (!MLX90393_setResolution(MLX90393_Y,   MLX90393_RES_16)) {
    return false;
  }
  if (!MLX90393_setResolution(MLX90393_Z,   MLX90393_RES_16)) {
    return false;
  }

  /* Set oversampling. */
  if (!MLX90393_setOversampling(MLX90393_OSR_2)) {
    return false;
  }

  /* Set digital filtering. */
  if (!MLX90393_setFilter(MLX90393_FILTER_3)) {
    return false;
  }

  /* set INT pin to output interrupt */
  if (!MLX90393_setTrigInt(false)) {
    return false;
  }

  u8 x = MLX90393_getResolution(MLX90393_X);
  u8 y = MLX90393_getResolution(MLX90393_Y);
  u8 z = MLX90393_getResolution(MLX90393_Z);


NRF_LOG_DEBUG("INIT MAG OK");
  return true;
}

/**
 * Perform a mode exit
 * @return True if the operation succeeded, otherwise false.
 */
 bool MLX90393_exitMode(void) {
  uint8_t tx[1] = {MLX90393_REG_EX};

  /* Perform the transaction. */
  return (MLX90393_transceive(tx, sizeof(tx), NULL,0,100) == MLX90393_STATUS_OK);
}





/**
 * Perform a soft reset
 * @return True if the operation succeeded, otherwise false.
 */
 bool MLX90393_reset(void) {
  uint8_t tx[1] = {MLX90393_REG_RT};


  /* Perform the transaction. */
  if (MLX90393_transceive(tx, sizeof(tx), NULL, 0,100) != MLX90393_STATUS_RESET) {
    return false;
  }
  return true;
}

/**
 * Sets the sensor gain to the specified level.
 * @param gain  The gain level to set.
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_setGain(mlx90393_gain_t gain) {


  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF1, &data);
 _gain = gain;
  // mask off gain bits
  data &= ~0x0070;
  // set gain bits
  data |= gain << MLX90393_GAIN_SHIFT;

  return MLX90393_writeRegister(MLX90393_CONF1, data);
}

/**
 * Gets the current sensor gain.
 *
 * @return An enum containing the current gain level.
 */
mlx90393_gain_t MLX90393_getGain(void) {
  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF1, &data);

  // mask off gain bits
  data &= 0x0070;

  return (mlx90393_gain_t)(data >> 4);
}







/**
 * Gets the current digital filter setting.
 * @return An enum containing the current digital filter setting.
 */
enum mlx90393_filter MLX90393_getFilter(void) { return _dig_filt; }



/**
 * Gets the current oversampling setting.
 * @return An enum containing the current oversampling setting.
 */
enum mlx90393_oversampling MLX90393_getOversampling(void) {
  return _osr;
}


/**
 * Sets the TRIG_INT pin to the specified function.
 *
 * @param state  'true/1' sets the pin to INT, 'false/0' to TRIG.
 *
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_setTrigInt(bool state) {
  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF2, &data);

  // mask off trigint bit
  data &= ~0x8000;

  // set trigint bit if desired
  if (state) {
    /* Set the INT, highest bit */
    data |= 0x8000;
  }

  return MLX90393_writeRegister(MLX90393_CONF2, data);
}


/**
 * Begin a single measurement on all axes
 *
 * @return True on command success
 */
bool MLX90393_startSingleMeasurement(void) {
  uint8_t tx[1] = {MLX90393_REG_SM | MLX90393_AXIS_ALL};

  /* Set the device to single measurement mode */
  uint8_t stat = MLX90393_transceive(tx, sizeof(tx), NULL, 0,0);
  if ((stat == MLX90393_STATUS_OK) || (stat == MLX90393_STATUS_SMMODE)) {
    return true;
  }
  return false;
}

/**
 * Reads data from data register & returns the results.
 *
 * @param x     Pointer to where the 'x' value should be stored.
 * @param y     Pointer to where the 'y' value should be stored.
 * @param z     Pointer to where the 'z' value should be stored.
 *
 * @return True on command success
 */
bool MLX90393_readMeasurement(float *x, float *y, float *z) {
  uint8_t tx[1] = {MLX90393_REG_RM | MLX90393_AXIS_ALL};
  uint8_t rx[6] = {0};

  /* Read a single data sample. */
  if (MLX90393_transceive(tx, sizeof(tx), rx, sizeof(rx),10) != MLX90393_STATUS_OK) {
    return false;
  }

  int16_t xi, yi, zi;

  /* Convert data to uT and float. */
  xi = (rx[0] << 8) | rx[1];
  yi = (rx[2] << 8) | rx[3];
  zi = (rx[4] << 8) | rx[5];

  if (_res_x == MLX90393_RES_18)
    xi -= 0x8000;
  if (_res_x == MLX90393_RES_19)
    xi -= 0x4000;
  if (_res_y == MLX90393_RES_18)
    yi -= 0x8000;
  if (_res_y == MLX90393_RES_19)
    yi -= 0x4000;
  if (_res_z == MLX90393_RES_18)
    zi -= 0x8000;
  if (_res_z == MLX90393_RES_19)
    zi -= 0x4000;

  *x = (float)xi * mlx90393_lsb_lookup[0][_gain][_res_z][0];
  *y = (float)yi * mlx90393_lsb_lookup[0][_gain][_res_y][0];
  *z = -(float)zi * mlx90393_lsb_lookup[0][_gain][_res_x][1];

  return true;
}



bool MLX90393_readMeasurement_z(float *z) {
  uint8_t tx[1] = {MLX90393_REG_RM | MLX90393_AXIS_Z};
  uint8_t rx[2] = {0};

  /* Read a single data sample. */
  if (MLX90393_transceive(tx, sizeof(tx), rx, sizeof(rx),10) != MLX90393_STATUS_OK) {
    return false;
  }

  int16_t zi;

  /* Convert data to uT and float. */
  zi = (rx[0] << 8) | rx[1];

  if (_res_z == MLX90393_RES_18)
    zi -= 0x8000;
  if (_res_z == MLX90393_RES_19)
    zi -= 0x4000;

  *z = (float)zi * mlx90393_lsb_lookup[0][_gain][_res_z][1];

  return true;
}


/**
 * Performs a single X/Y/Z conversion and returns the results.
 *
 * @param x     Pointer to where the 'x' value should be stored.
 * @param y     Pointer to where the 'y' value should be stored.
 * @param z     Pointer to where the 'z' value should be stored.
 *
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_readData(float *x, float *y, float *z) {
  if (!MLX90393_startSingleMeasurement())
    return false;
  // See MLX90393 Getting Started Guide for fancy formula
  // tconv = f(OSR, DIG_FILT, OSR2, ZYXT)
  // For now, using Table 18 from datasheet
  // Without +10ms delay measurement doesn't always seem to work

  //nrf_delay_ms(mlx90393_tconv[_dig_filt][_osr] + 50);
   tempo( mlx90393_tconv[_dig_filt][_osr] + 50);
   //MLX90393_readMeasurement(x, y, z);
  // MLX90393_readMeasurement_z(z); 
return(   MLX90393_readMeasurement(x, y, z));

}



/**
 * Performs a full read/write transaction with the sensor.
 *
 * @param txbuf     Pointer the the buffer containing the data to write.
 * @param txlen     The number of bytes to write.
 * @param rxbuf     Pointer to an appropriately large buffer where data read
 *                  back will be written.
 * @param rxlen     The number of bytes to read back (not including the
 *                  mandatory status byte that is always returned).
 *
 * @return The status byte from the IC.
 */
uint8_t  MLX90393_transceive(uint8_t *txbuf, uint8_t txlen,
                                      uint8_t *rxbuf, uint8_t rxlen,
                                      uint8_t interdelay) {
  uint8_t status = 0;
  uint8_t i;
  uint8_t rxbuf2[rxlen + 2];
  spi_transfer(SPI_MAG, CS_MAG, true, txbuf, txlen, rxbuf2,  rxlen + 2);
    status = rxbuf2[1];
    for (i = 0; i < rxlen; i++) {
      rxbuf[i] = rxbuf2[i + 2];
    }
    // nrf_delay_ms(interdelay);
  tempo( interdelay);

  return (status >> 2);
}


/**************************************************************************/
/*!
    @brief  Gets the sensor_t device data, Adafruit Unified Sensor format
    @param  sensor Pointer to an Adafruit Unified sensor_t object that we'll
   fill in
*/
/**************************************************************************/
void MLX90393_getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy(sensor->name, "MLX90393", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name) - 1] = 0;
  sensor->version = 1;
  sensor->sensor_id = _sensorID;
  sensor->type = SENSOR_TYPE_MAGNETIC_FIELD;
  sensor->min_delay = 0;
  sensor->min_value = -50000; // -50 gauss in uTesla
  sensor->max_value = 50000;  // +50 gauss in uTesla
  sensor->resolution = 0.15;  // 100/16-bit uTesla per LSB
}


bool MLX90393_readRegister(uint8_t reg, uint16_t *data) {
  uint8_t tx[2] = {
      MLX90393_REG_RR,
      (uint8_t)(reg << 2)
    //  (uint8_t) 0,
    //  (uint8_t) 0,
    //  (uint8_t) 0,
      }; // the register itself, shift up by 2 bits!

  uint8_t rx[4];

  /* Perform the transaction. */
  if (MLX90393_transceive(tx, sizeof(tx), rx, sizeof(rx),20) != MLX90393_STATUS_OK) {
    return false;
  }

  *data = ((uint16_t)rx[2] << 8) | rx[3];

  return true;
}


bool MLX90393_writeRegister(uint8_t reg, uint16_t data) {
  uint8_t tx[4] = {
      MLX90393_REG_WR,
      (uint8_t)(data >> 8),   // high byte
      (uint8_t)(data & 0xFF), // low byte
      (uint8_t)(reg << 2)};   // the register itself, shift up by 2 bits!



  /* Perform the transaction. */
  return (MLX90393_transceive(tx, sizeof(tx), NULL, 0,20) == MLX90393_STATUS_OK);
}


/**
 * Sets the sensor resolution to the specified level.
 * @param axis  The axis to set.
 * @param resolution  The resolution level to set.
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_setResolution(enum mlx90393_axis axis, enum mlx90393_resolution resolution) {

  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF3, &data);

  switch (axis) {
  case MLX90393_X:
    _res_x = resolution;
    data &= ~0x0060;
    data |= resolution << 5;
    break;
  case MLX90393_Y:
    _res_y = resolution;
    data &= ~0x0180;
    data |= resolution << 7;
    break;
  case MLX90393_Z:
    _res_z = resolution;
    data &= ~0x0600;
    data |= resolution << 9;
    break;
  }

  return MLX90393_writeRegister(MLX90393_CONF3, data);
}



/**
 * Gets the current sensor resolution.
 * @param axis  The axis to get.
 * @return An enum containing the current resolution.
 */
enum mlx90393_resolution MLX90393_getResolution(enum mlx90393_axis axis) {
  switch (axis) {
  case MLX90393_X:
    return   _res_x;
  case MLX90393_Y:
    return _res_y;
  case MLX90393_Z:
    return _res_z;
  }
  // shouldn't get here, but to make compiler happy...
  return _res_x;
}

/**
 * Sets the oversampling.
 * @param oversampling The oversampling value to use.
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_setOversampling(
    enum mlx90393_oversampling oversampling) {
  _osr = oversampling;

  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF3, &data);

  data &= ~0x03;
  data |= oversampling;

  return MLX90393_writeRegister(MLX90393_CONF3, data);
}

/**
 * Sets the digital filter.
 * @param filter The digital filter setting.
 * @return True if the operation succeeded, otherwise false.
 */
bool MLX90393_setFilter(enum mlx90393_filter filter) {
  _dig_filt = filter;

  uint16_t data;
  MLX90393_readRegister(MLX90393_CONF3, &data);

  data &= ~0x1C;
  data |= filter << 2;

  return MLX90393_writeRegister(MLX90393_CONF3, data);
}


