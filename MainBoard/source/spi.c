
#include "Globale.h"

#include "nrf_gpio.h"
#include "nrf_log.h"






// limitation that we can only xfer 255 bytes at a time
#define SPI_CHUNK_SIZE 255

// keep in a struct for now as we may need to add more state params
typedef struct
{
    nrf_drv_spi_t spi;    
} SPI_T;

static SPI_T _spi_0 = {
    .spi = NRF_DRV_SPI_INSTANCE(0),
};
static SPI_T _spi_1 = {
    .spi = NRF_DRV_SPI_INSTANCE(1),
};




/**
 * @brief Open SPI port.
 * 
 * @param instance 
 * @param frequency 
 * @param mode 
 * @param miso_pin 
 * @param mosi_pin 
 * @param sck_pin 
 * @param cs_pin 
 * @param cs_pin_active_low 
 * @return uint32_t nrf error code
 */
uint32_t spi_open(SPI_INSTANCE_T instance, nrf_drv_spi_frequency_t frequency, nrf_drv_spi_mode_t mode,
    int32_t miso_pin, int32_t mosi_pin, int32_t sck_pin, int32_t cs_pin, bool cs_pin_active_low)
{
    SPI_T *pspi;
    uint32_t err_code;
    
    switch(instance)
    {
        case SPI_0:
            pspi = &_spi_0;
           
            break;

        case SPI_1:
            pspi = &_spi_1;
           
            break;    
       
        default:
            NRF_LOG_ERROR("invalid spi instance!");
            return NRF_ERROR_INVALID_PARAM;
    }

    if(cs_pin != SPI_INVALID_SS_PIN)
    {
        nrf_gpio_cfg_output(cs_pin);
        if(cs_pin_active_low)
            nrf_gpio_pin_set(cs_pin);
        else
            nrf_gpio_pin_clear(cs_pin);
    }

    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = NRF_DRV_SPI_PIN_NOT_USED;
    spi_config.miso_pin = miso_pin;
    spi_config.mosi_pin = mosi_pin;
    spi_config.sck_pin  = sck_pin;
    spi_config.frequency = frequency;
    spi_config.mode = mode;
    spi_config.bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;
    err_code = nrf_drv_spi_init(&pspi->spi, &spi_config, NULL, NULL);

    // NRF_ERROR_INVALID_STATE just means we already initialized it
    if((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_INVALID_STATE))
    {
        NRF_LOG_ERROR("failed to configure spi! error = %ld", err_code);
    }

    return err_code;
}

/**
 * @brief Close the SPI port.
 * 
 * @param instance 
 */
void spi_close(SPI_INSTANCE_T instance)
{
    SPI_T *pspi;
        
    switch(instance)
    {
        case SPI_0:
            pspi = &_spi_0;
            break;

        case SPI_1:
            pspi = &_spi_1;
            break;
       
       
        default:
            NRF_LOG_ERROR("invalid spi instance!");
            return;
    }

    nrf_drv_spi_uninit(&pspi->spi);
}

/**
 * @brief Transfer data to/from SPI port.  SPI can be a shared resource, instance mutexes are used and
 * will cause a wait until the resource is freed.
 * 
 * @param instance 
 * @param ss_pin 
 * @param ptx 
 * @param tx_length 
 * @param prx 
 * @param rx_length 
 * @return uint32_t NRF error code
 */
uint32_t spi_transfer(SPI_INSTANCE_T instance, int32_t cs_pin, bool cs_pin_active_low, void *ptx,
    int32_t tx_length, void *prx, int32_t rx_length)
{
    SPI_T *pspi;
    uint32_t err_code;
    int32_t write_index = 0;
    int32_t read_index = 0;
    int32_t write_byte_count = 0;
    int32_t read_byte_count = 0;
    uint8_t *write_buffer = (uint8_t*)ptx;
    uint8_t *read_buffer = (uint8_t*)prx;
        
    switch(instance)
    {
        case SPI_0:
            pspi = &_spi_0;
           
            break;
        case SPI_1:
            pspi = &_spi_1;
           
            break;
      
        default:
            NRF_LOG_ERROR("invalid spi instance!");
            return NRF_ERROR_INVALID_PARAM;
    }

    if(cs_pin != SPI_INVALID_SS_PIN)
    {
        if(cs_pin_active_low)
            nrf_gpio_pin_clear(cs_pin);
        else
            nrf_gpio_pin_set(cs_pin);
    }

    while(write_index < tx_length || read_index < rx_length)
    {
        write_byte_count = tx_length - write_index;
        if(write_byte_count > SPI_CHUNK_SIZE)
            write_byte_count = SPI_CHUNK_SIZE;

        read_byte_count = rx_length - read_index;
        if(read_byte_count > SPI_CHUNK_SIZE)
            read_byte_count = SPI_CHUNK_SIZE;
        err_code = nrf_drv_spi_transfer(&pspi->spi, &write_buffer[write_index], write_byte_count, &read_buffer[read_index], read_byte_count);
        if(err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("failed to spi transfer! error %ld", err_code);
            break;
        }

        write_index += write_byte_count;
        read_index += read_byte_count;
    }

    if(cs_pin != SPI_INVALID_SS_PIN)
    {
        if(cs_pin_active_low)
            nrf_gpio_pin_set(cs_pin);
        else
            nrf_gpio_pin_clear(cs_pin);
    }

  

    if(err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("failed to transfer spi! error = %ld", err_code);
    }

    return err_code;
}
