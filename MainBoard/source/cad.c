#include "cad.h"

#include "nrfx_saadc.h"
#include "nrf_drv_saadc.h"


#define SAMPLES_IN_BUFFER 1




static nrf_saadc_value_t m_buffer[SAMPLES_IN_BUFFER];
int16_t adc_result=0;

void idle_state_handle()
{
  nrf_pwr_mgmt_run();
}

void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
  if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
  {
    ret_code_t err_code;
    
    err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);
    adc_result = p_event->data.done.p_buffer[0];
  }
}

void init_saadc()
{
  ret_code_t err_code;
  /*Config the channel*/
  nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_VDD);
channel_config.reference= NRF_SAADC_REFERENCE_VDD4;
//channel_config.reference= SAADC_CH_CONFIG_REFSEL_Internal;
  
  err_code = nrf_drv_saadc_init(NULL, NULL);
  APP_ERROR_CHECK(err_code);
  
  err_code = nrf_drv_saadc_channel_init(0, &channel_config);
  APP_ERROR_CHECK(err_code);
  
 // err_code = nrf_drv_saadc_buffer_convert(m_buffer,SAMPLES_IN_BUFFER);
 // APP_ERROR_CHECK(err_code);
}

float read_adc(void)
{
   u16 adc_result =0;
   float f=0;

  nrfx_saadc_sample_convert(NRF_SAADC_INPUT_VDD,&adc_result);

f= adc_result*3.3/4*6/1024;
//f= adc_result;
//f=f*1.06*6/1024;
return( f);
}
