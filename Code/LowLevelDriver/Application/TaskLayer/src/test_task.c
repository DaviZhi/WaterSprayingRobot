#include "test_task.h"
#include "bldc_driver.h"
#include "rmt_driver.h"
#include "chassis.h"

bldc_set_t BLDC_Set[4];
rmt_info_t Rmt_Info;
chassis_set_t Chassis_Set;

xQueueHandle xRemoteHandle;

int16_t Chassis_Target_Set[BLDC_NUM];	//debug
int16_t Chassis_Vx_Set, Chassis_Vy_Set, Chassis_Vz_Set;	//debug

void ChassisTask(void* argument)
{
	Chassis_Init(&Chassis_Set);
	vTaskDelay(pdMS_TO_TICKS(1));
	Chassis_BrakeSet(&Chassis_Set, CHASSIS_LOOSE);
	Chassis_Start(&Chassis_Set);
	
	for(;;)
	{	
		if(xQueueReceive(xRemoteHandle, Chassis_Set.chassis_receive_remote, portMAX_DELAY) == pdPASS)
		{
			Chassis_RemoteToSpeed(&Chassis_Set, Chassis_Set.chassis_receive_remote[1], 
								  Chassis_Set.chassis_receive_remote[0], Chassis_Set.chassis_receive_remote[2]);
			
			Chassis_SpeedTransform(&Chassis_Set);
			
			Chassis_TargetToPWM(&Chassis_Set);
			
			//debug
			Chassis_Vx_Set = Chassis_Set.chassis_vx_set;
			Chassis_Vy_Set = Chassis_Set.chassis_vy_set;
			Chassis_Vz_Set = Chassis_Set.chassis_vz_set;
			
			Chassis_Target_Set[LB] = Chassis_Set.chassis_target_set[LB];
			Chassis_Target_Set[LF] = Chassis_Set.chassis_target_set[LF];
			Chassis_Target_Set[RF] = Chassis_Set.chassis_target_set[RF];
			Chassis_Target_Set[RB] = Chassis_Set.chassis_target_set[RB];
		}

		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void RemoteTask(void* argument)
{
	uint16_t rmt_ch_send_buf[3] = {0,0,0};
	xRemoteHandle = xQueueCreate(9, sizeof(rmt_ch_send_buf));
		
	Remote_Init(&Rmt_Info);
	for(;;)
	{
		Remote_ChannelGet(&Rmt_Info);
		Remote_ChannelHandler(&Rmt_Info);
		
		rmt_ch_send_buf[0] = Rmt_Info.sbus_channel[0];
		rmt_ch_send_buf[1] = Rmt_Info.sbus_channel[1];
		rmt_ch_send_buf[2] = Rmt_Info.sbus_channel[3];
		
		xQueueSendToBack(xRemoteHandle, rmt_ch_send_buf, portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}
