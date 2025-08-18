#ifndef RMT_DRIVER_H
#define RMT_DRIVER_H

#include "usart.h"
#include "gpio.h"

#include "filter.h"
#include "dev.h"

/* Private struct----------*/
typedef struct
{
	uint8_t sbus_data[25];
	uint16_t sbus_channel[6];
	uint16_t sbus_channel_ori[6];
	filter_info_t rmt_filter_info[4];
	dev_status_e rmt_status;
	
}rmt_info_t;

/* Remote_Exported function------------------------------------------------------*/
void Remote_ChannelGet(rmt_info_t* rmt_info);
void Remote_ChannelOneToFour_Handler(rmt_info_t* rmt_info);

#endif
