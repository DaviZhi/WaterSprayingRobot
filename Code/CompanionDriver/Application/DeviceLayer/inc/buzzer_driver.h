#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include "driver/gpio.h"

typedef struct
{
    gpio_config_t buzzer_gpio_config;
}buzzer_config_t;

void Buzzer_Init(buzzer_config_t* buzzer_config);
void Buzzer_SetLevel(uint32_t level);

#endif