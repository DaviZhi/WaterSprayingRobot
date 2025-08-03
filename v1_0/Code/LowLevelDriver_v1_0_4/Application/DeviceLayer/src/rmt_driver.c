#include "rmt_driver.h"
#include "rmt_xdefine.h"
#include "filter.h"

uint16_t Remote0,Remote2,Remote1,Remote3;	//test param

/**	
 * @brief Receive data from receiver and convert them into channel value, every 11 bit data compose a channel.
 * @param rmt_info structure ptr.
 */
void Remote_ChannelGet(rmt_info_t* rmt_info)
{
	HAL_UART_Receive_DMA(&huart2, rmt_info->sbus_data, sizeof(rmt_info->sbus_data));
	
	rmt_info->sbus_channel_ori[0] = (rmt_info->sbus_data[1] | (rmt_info->sbus_data[2] << 8)) & 0x07FF;
	rmt_info->sbus_channel_ori[1] = (rmt_info->sbus_data[2] >> 3 | (rmt_info->sbus_data[3] << 5)) & 0x07FF;
	rmt_info->sbus_channel_ori[2] = (rmt_info->sbus_data[3] >> 6 | (rmt_info->sbus_data[4] << 2) | 
	(rmt_info->sbus_data[5] << 10)) & 0x07FF;
	rmt_info->sbus_channel_ori[3] = (rmt_info->sbus_data[5] >> 1 | (rmt_info->sbus_data[6] << 7)) & 0x07FF;
	rmt_info->sbus_channel_ori[4] = (rmt_info->sbus_data[6] >> 4 | (rmt_info->sbus_data[7] << 4)) & 0x07FF;
	rmt_info->sbus_channel_ori[5] = (rmt_info->sbus_data[7] >> 7 | (rmt_info->sbus_data[8] << 1) | 
	(rmt_info->sbus_data[9] << 9)) & 0x07FF;
	
	//debug
	Remote2 = rmt_info->sbus_channel[2];
	Remote0 = rmt_info->sbus_channel[0];
	Remote1 = rmt_info->sbus_channel[1];
	Remote3 = rmt_info->sbus_channel[3];
}

/**	
 * @brief Remote data handler(ch1 to ch4), filt remote original data.
 * @param rmt_info structure ptr.
 * @note The chart of remote handler shows general process:
 *  ---------------                    ---------------                    --------------
 * |               | limiting filter  |               | low-pass filter  |              | 
 * | original data |----------------->| channel_temp1 |----------------->| sbus_channel |
 * |               |                  |               |                  |              |
 *  ---------------                    ---------------                    --------------
 */
void Remote_ChannelOneToFour_Handler(rmt_info_t* rmt_info)
{
	volatile static uint16_t channel_temp1[4];
	volatile static uint16_t channel_temp2[4];
	const uint16_t threshold = 300;
	const float alpha = 0.8;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		channel_temp1[i] = Filter_Limiting(rmt_info->sbus_channel_ori[i], threshold);
	}
	for(uint8_t i = 0; i < 4; i++)
	{
		rmt_info->sbus_channel[i] = Filter_LowPass(channel_temp1[i], alpha);
	}
	
	//debug
//	for(uint8_t i = 0; i < 4; i++)
//	{
//		channel_temp1[i] = Filter_Limiting(rmt_info->sbus_channel_ori[i], threshold);
//		rmt_info->sbus_channel[i] = Filter_LowPass(channel_temp1[i], alpha);
//	}
}
