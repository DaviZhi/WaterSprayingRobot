#include "led_driver.h"
#include "led_xdefine.h"
#include <stdio.h>

void LED_Init(led_config_t* led_config)
{
    led_config[WARNNING_YELLOW].led_gpio_config.pin_bit_mask = 1ULL << LED_WARNNING_PIN;
    led_config[ERROR_RED].led_gpio_config.pin_bit_mask = 1ULL << LED_ERROR_PIN;
    led_config[NORMAL_GREEN].led_gpio_config.pin_bit_mask = 1ULL << LED_NORMAL_PIN;
    led_config[SLEEP_BLUE].led_gpio_config.pin_bit_mask = 1ULL << LED_SLEEP_PIN;
    for(uint8_t i = 0; i < LED_TYPE_NUM; i++)
    {
        led_config[i].led_gpio_config.intr_type = GPIO_INTR_DISABLE;
        led_config[i].led_gpio_config.mode = GPIO_MODE_OUTPUT;
        led_config[i].led_gpio_config.pull_down_en = GPIO_PULLDOWN_ENABLE;
        led_config[i].led_gpio_config.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&led_config[i].led_gpio_config);
    }
    // Turn off all LEDs at start
    gpio_set_level(LED_WARNNING_PIN, LED_OFF);
    gpio_set_level(LED_ERROR_PIN, LED_OFF);
    gpio_set_level(LED_NORMAL_PIN, LED_OFF);
    gpio_set_level(LED_SLEEP_PIN, LED_OFF);
}

void LED_SetLevel(led_type_e led_type, uint32_t level)
{
    switch (led_type)
    {
        case NORMAL_GREEN:
        gpio_set_level(LED_NORMAL_PIN, level);
        break;

        case ERROR_RED:
        gpio_set_level(LED_ERROR_PIN, level);
        break;

        case WARNNING_YELLOW:
        gpio_set_level(LED_WARNNING_PIN, level);
        break;

        case SLEEP_BLUE:
        gpio_set_level(LED_SLEEP_PIN, level);
        break;

        default:
        printf("Error: Maximum of LED type is 4, out of maximum LED pin type!");
        break;
    }
}