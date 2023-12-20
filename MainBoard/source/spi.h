#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stdbool.h>
#include "nrf_drv_spi.h"

typedef enum
{
    SPI_0,
    SPI_1,
    SPI_2,
} SPI_INSTANCE_T;

#define SPI_INVALID_SS_PIN -1

uint32_t spi_open(SPI_INSTANCE_T instance, nrf_drv_spi_frequency_t frequency, nrf_drv_spi_mode_t mode,
    int32_t miso_pin, int32_t mosi_pin, int32_t sck_pin, int32_t cs_pin, bool cs_pin_active_low);
void spi_close(SPI_INSTANCE_T instance);
uint32_t spi_transfer(SPI_INSTANCE_T instance, int32_t cs_pin, bool cs_pin_active_low, void *ptx, int32_t tx_length, void *prx, int32_t rx_length);
#endif