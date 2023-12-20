
#ifndef GLOBALE_H
#define GLOBALE_H



#include "DefTypes.h"
#include <stdint.h>
//#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "app_util_platform.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "app_error.h"
#include "app_util.h"
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_cdc_acm.h"
#include "app_usbd_serial_num.h"


#include "custom_board.h"


#include "nrf_drv_spi.h"
#include "spi.h"
#include "nrf_drv_spi.h"
#include "MA780.h"




#define CODE_PAGE_SIZE						0x1000
#define ADRESSE_FLASH_1						(0xf0000)

typedef struct
{
	char name[12];     /**< sensor name */
	int32_t version;   /**< version of the hardware + driver */
	int32_t sensor_id; /**< unique sensor identifier */
	int32_t type;      /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
	float max_value;   /**< maximum value of this sensor's value in SI units */
	float min_value;   /**< minimum value of this sensor's value in SI units */
	float resolution; /**< smallest difference between two values reported by this
						sensor */
	int32_t min_delay; /**< min delay in microseconds between events. zero = not a
							constant rate */
} sensor_t;


typedef struct
{
	float K_common;
	float angle_2_offset;
	float x_0_init;
	float x_0_offset;
} PARAM_VOLUME;


typedef struct
{
	float Ka_BxC3;
	float Kb_BxC3;
	float Ka_ByC3;
	float Kb_ByC3;
	float Ka_BzC3;
	float Kb_BzC3;
} PARAM_POSITION;



typedef  union {
	u32 u32_buffer[CODE_PAGE_SIZE/4];
	struct
	{
		u32 u32_boot;					/* indicateur de passage en Bootloader*/
		u8 u8_init_param;
   		PARAM_VOLUME Param_mesure_volume;
   		PARAM_POSITION Param_mesure_position;
 	} s_element;
} DEFINITION_FLASH1;



typedef 	struct
	{
		float number_of_turns;
		float confidence_index;
		float angle_1_comp;
		float angle_2_comp;
 	} RESULTAT_ALGO_VOLUME;



typedef 	struct
	{
		DEFINITION_FLASH1 *flash;
		RESULTAT_ALGO_VOLUME result;
 	} VOLUME;



typedef 	struct
	{
		float position;
		float angle;
		float BxC3_parasitic;
		float ByC3_parasitic;
		float BzC3_parasitic;
		float BxC3_comp;
		float ByC3_comp;
		float BzC3_comp;
 	} RESULTAT_POSITION;


typedef 	struct
	{
		DEFINITION_FLASH1 *flash;
		RESULTAT_POSITION result;
 	} POSITION;


extern  DEFINITION_FLASH1 param_flash;
extern  bool  ind_flash;
extern float  f_nombre_de_tour ;
extern VOLUME s_volume;
extern POSITION s_position; 


#endif
