#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "driver/gpio.h"

typedef enum
{
    NORMAL_GREEN,
    ERROR_RED,
    WARNNING_YELLOW,
    SLEEP_BLUE,
    LED_TYPE_NUM,
}led_type_e;

typedef struct
{
    gpio_config_t led_gpio_config;
}led_config_t;

void LED_Init(led_config_t* led_config);
void LED_SetLevel(led_type_e led_type, uint32_t level);

#endif