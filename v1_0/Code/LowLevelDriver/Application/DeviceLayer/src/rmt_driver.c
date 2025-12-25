#include "rmt_driver.h"
#include "rmt_xdefine.h"
#include "dev.h"

void Remote_Init(rmt_info_t* rmt_info)
{
//	Remote_ChannelGet(rmt_info);
	if(HAL_UART_Receive_DMA(&huart2, rmt_info->sbus_data, sizeof(rmt_info->sbus_data)) == HAL_OK)
	{
		/*sbus decode*/
		rmt_info->sbus_channel_ori[0] = (rmt_info->sbus_data[1] | (rmt_info->sbus_data[2] << 8)) & 0x07FF;
		rmt_info->sbus_channel_ori[1] = (rmt_info->sbus_data[2] >> 3 | (rmt_info->sbus_data[3] << 5)) & 0x07FF;
		rmt_info->sbus_channel_ori[2] = (rmt_info->sbus_data[3] >> 6 | (rmt_info->sbus_data[4] << 2) | 
		(rmt_info->sbus_data[5] << 10)) & 0x07FF;
		rmt_info->sbus_channel_ori[3] = (rmt_info->sbus_data[5] >> 1 | (rmt_info->sbus_data[6] << 7)) & 0x07FF;
		rmt_info->sbus_channel_ori[4] = (rmt_info->sbus_data[6] >> 4 | (rmt_info->sbus_data[7] << 4)) & 0x07FF;
		rmt_info->sbus_channel_ori[5] = (rmt_info->sbus_data[7] >> 7 | (rmt_info->sbus_data[8] << 1) | 
		(rmt_info->sbus_data[9] << 9)) & 0x07FF;
	}
	
	for(uint8_t i = 0; i < 4; i++)
	{
		rmt_info->rmt_filter_info[i].prev_value = rmt_info->sbus_channel_ori[i];
	}
}

uint16_t Remote, Remote_Ori;

/**	
 * @brief Receive data from receiver and convert them into channel value, every 11 bit data compose a channel.
 * @param rmt_info structure ptr.
 */
void Remote_ChannelGet(rmt_info_t* rmt_info)
{
	if(HAL_UART_Receive_DMA(&huart2, rmt_info->sbus_data, sizeof(rmt_info->sbus_data)) != HAL_OK)
	{
		rmt_info->rmt_status = DEV_ERR;
	}
	else
	{
		rmt_info->rmt_status = DEV_OK;
		
		/*sbus decode*/
		rmt_info->sbus_channel_ori[0] = (rmt_info->sbus_data[1] | (rmt_info->sbus_data[2] << 8)) & 0x07FF;
		rmt_info->sbus_channel_ori[1] = (rmt_info->sbus_data[2] >> 3 | (rmt_info->sbus_data[3] << 5)) & 0x07FF;
		rmt_info->sbus_channel_ori[2] = (rmt_info->sbus_data[3] >> 6 | (rmt_info->sbus_data[4] << 2) | 
		(rmt_info->sbus_data[5] << 10)) & 0x07FF;
		rmt_info->sbus_channel_ori[3] = (rmt_info->sbus_data[5] >> 1 | (rmt_info->sbus_data[6] << 7)) & 0x07FF;
		rmt_info->sbus_channel_ori[4] = (rmt_info->sbus_data[6] >> 4 | (rmt_info->sbus_data[7] << 4)) & 0x07FF;
		rmt_info->sbus_channel_ori[5] = (rmt_info->sbus_data[7] >> 7 | (rmt_info->sbus_data[8] << 1) | 
		(rmt_info->sbus_data[9] << 9)) & 0x07FF;
		
		Remote_Ori = rmt_info->sbus_channel_ori[3];	//debug
	}
}

/**	
 * @brief Remote data handler(ch1 to ch4), filt remote original data.
 * @param rmt_info structure ptr.
 * @note The chart of remote handler shows general process:
 *  ---------------                    --------------
 * |               | low-pass filter  |              | 
 * | original data |----------------->| sbus_channel |
 * |               |                  |              |
 *  ---------------                    --------------
 */
void Remote_ChannelOneToFour_Handler(rmt_info_t* rmt_info)
{
	static const float alpha = 0.04f;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		rmt_info->sbus_channel[i] = Filter_LowPass(&rmt_info->rmt_filter_info[i], 
												   (float)rmt_info->sbus_channel_ori[i], alpha);
	}
	Remote = rmt_info->sbus_channel[3];
}
