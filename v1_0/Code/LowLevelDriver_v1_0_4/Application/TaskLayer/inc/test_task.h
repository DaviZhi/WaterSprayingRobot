#ifndef TEST_TASK_H
#define TEST_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

void StartDefaultTask(void const * argument);
void StopTask(void *argument);

#endif
