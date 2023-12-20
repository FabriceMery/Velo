

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf.h"
#include "nrf_soc.h"
#include "nordic_common.h"
#include "boards.h"
#include "app_timer.h"
#include "app_util.h"
#include "nrf_fstorage.h"

#ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_fstorage_sd.h"
#else
#include "nrf_drv_clock.h"
#include "nrf_fstorage_nvmc.h"
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#include "Globale.h"


static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);
static bool flash_erase_ok = true;
static bool flash_write_ok = true;



NRF_FSTORAGE_DEF(nrf_fstorage_t fstorage) =
{
    /* Set a handler for fstorage events. */
    .evt_handler = fstorage_evt_handler,
  
    .start_addr = 0xF0000,
    .end_addr   = 0xFffff,
};



/**@brief   Helper function to obtain the last address on the last page of the on-chip flash that
 *          can be used to write user data.
 */
static uint32_t nrf5_flash_end_addr_get()
{
    uint32_t const bootloader_addr = BOOTLOADER_ADDRESS;
    uint32_t const page_sz         = NRF_FICR->CODEPAGESIZE;
    uint32_t const code_sz         = NRF_FICR->CODESIZE;

    return (bootloader_addr != 0xFFFFFFFF ?
            bootloader_addr : (code_sz * page_sz));
}



static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{



  

    if (p_evt->result != NRF_SUCCESS)
    {
        NRF_LOG_INFO("--> Event received: ERROR while executing an fstorage operation.");
        return;
    }

    switch (p_evt->id)
    {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
        {
             NRF_LOG_INFO("--> Event received: wrote %d bytes at address 0x%x.",
                         p_evt->len, p_evt->addr);
             flash_write_ok = true; 


        } break;

        case NRF_FSTORAGE_EVT_ERASE_RESULT:
        {
            NRF_LOG_INFO("--> Event received: erased %d page from address 0x%x.",
                         p_evt->len, p_evt->addr);
           flash_erase_ok = true;
   
        } break;

        default:
            break;
    }
}


void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage)
{
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage))
    {
        (void) sd_app_evt_wait();
    }
}



void init_flash(void)
{
    ret_code_t rc;
    nrf_fstorage_api_t * p_fs_api;   
    p_fs_api = &nrf_fstorage_sd;
    rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(rc);
}


void test_flash(void)
{
      ret_code_t rc;
  unsigned char buffer[200];
  unsigned char *p= 0xF0000;
      nrf_fstorage_api_t * p_fs_api;

    p_fs_api = &nrf_fstorage_sd;
  
  
      rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(rc);
  //  wait_for_flash_ready(&fstorage);

  //nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    //  nrf_fstorage_write(&fstorage, 0x3e000, m_hello_world, sizeof(m_hello_world), NULL);

  flash_erase_ok = false; 
 rc = nrf_fstorage_erase(
 &fstorage, /* The instance to use. */
 0xF0000, /* The address of the flash pages to erase. */
1, /* The number of pages to erase. */
 NULL /* Optional parameter, backend-dependent. */
);

while( flash_erase_ok == false);

memcpy(buffer,p,50);
 flash_write_ok = false;
  rc = nrf_fstorage_write(&fstorage, 0xF0000, "12345678", 8, NULL);
 flash_write_ok = false;
while( flash_write_ok == false);


memcpy(buffer,p,50);
  
}


void Write_data_to_flash( u32 *p_flash,u32 AdresseFlash)
{
  ret_code_t rc;

  unsigned char buffer[200];
    unsigned char *p= AdresseFlash;
  flash_erase_ok = false; 
 rc = nrf_fstorage_erase( &fstorage, AdresseFlash, 1, NULL );

while( flash_erase_ok == false);

memcpy(buffer,p,50);
 flash_write_ok = false;
  rc = nrf_fstorage_write(&fstorage, AdresseFlash, p_flash, CODE_PAGE_SIZE/4, NULL);
 flash_write_ok = false;
while( flash_write_ok == false);


memcpy(buffer,p,50);
  
}



/**
 * @}
 */
