#include "buzzer_driver.h"

void Buzzer_Init(buzzer_config_t* buzzer_config)
{
    buzzer_config->buzzer_gpio_config.pin_bit_mask = 1ULL << BUZZER_PIN;
    buzzer_config->buzzer_gpio_config.intr_type = GPIO_INTR_DISABLE;
    buzzer_config->buzzer_gpio_config.mode = GPIO_MODE_OUTPUT;
    buzzer_config->buzzer_gpio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    buzzer_config->buzzer_gpio_config.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&buzzer_config->buzzer_gpio_config);
    // Turn off buzzer at start
    gpio_set_level(BUZZER_PIN, BUZZER_OFF);
}

void Buzzer_SetLevel(uint32_t level)
{
    gpio_set_level(BUZZER_PIN, level);
}