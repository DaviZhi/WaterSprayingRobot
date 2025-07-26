#include "rmt_driver.h"

void Remote_ChannelGet(rmt_info_t* rmt_info)
{
	HAL_UART_Receive_DMA(&huart2, rmt_info->sbus_data, sizeof(rmt_info->sbus_data));
	
	rmt_info->sbus_channel[0] = (rmt_info->sbus_data[1] | (rmt_info->sbus_data[2] << 8)) & 0x07FF;
	rmt_info->sbus_channel[1] = (rmt_info->sbus_data[2] >> 3 | (rmt_info->sbus_data[3] << 5)) & 0x07FF;
	rmt_info->sbus_channel[2] = (rmt_info->sbus_data[3] >> 6 | (rmt_info->sbus_data[4] << 2) | 
	(rmt_info->sbus_data[5] << 10)) & 0x07FF;
	rmt_info->sbus_channel[3] = (rmt_info->sbus_data[5] >> 1 | (rmt_info->sbus_data[6] << 7)) & 0x07FF;
	rmt_info->sbus_channel[4] = (rmt_info->sbus_data[6] >> 4 | (rmt_info->sbus_data[7] << 4)) & 0x07FF;
	rmt_info->sbus_channel[5] = (rmt_info->sbus_data[7] >> 7 | (rmt_info->sbus_data[8] << 1) | 
	(rmt_info->sbus_data[9] << 9)) & 0x07FF;
}
