#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include "driver/gpio.h"

#define BUZZER_PIN  13
#define BUZZER_ON   0
#define BUZZER_OFF  1

typedef struct
{
    gpio_config_t buzzer_gpio_config;
}buzzer_config_t;

void Buzzer_Init(buzzer_config_t* buzzer_config);
void Buzzer_SetLevel(uint32_t level);

#endif