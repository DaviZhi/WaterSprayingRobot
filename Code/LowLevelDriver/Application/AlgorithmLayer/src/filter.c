#include "filter.h"

/**	
 * @brief Low pass filter implementation.
 * @param filter_info structure ptr
 * @param new sample value
 * @param alpha factor
 * @return filtered value
 */
uint16_t Filter_LowPass(filter_info_t* filter_info, float sample_new, float alpha)
{
	filter_info->new_value = alpha * sample_new + (1 - alpha) * filter_info->prev_value;
	filter_info->prev_value = filter_info->new_value;
	
	return (uint16_t)filter_info->new_value;
}

/**	
 * @brief Limiting filter implementation.
 * @param filter_info structure ptr
 * @param data for limiting
 * @param limit threshold
 * @return filtered value
 */
uint16_t Filter_Limiting(filter_info_t* filter_info, float data, float limit_threshold)
{
	if(fabs(data - filter_info->prev_value) > limit_threshold)
	{
		filter_info->new_value = filter_info->prev_value;
	}
	else
	{
		filter_info->new_value = data;
	}
	filter_info->prev_value = filter_info->new_value;
	
	return (uint16_t)filter_info->new_value;
}
