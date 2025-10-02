#ifndef TEST_TASK_H
#define TEST_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

void StartDefaultTask(void* argument);
void Task1(void* argument);

#endif
