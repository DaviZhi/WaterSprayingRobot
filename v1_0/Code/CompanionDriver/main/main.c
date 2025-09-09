#include <stdio.h>
#include <string.h>
#include "comp_driver_ver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "display_driver.h"
#include "led_driver.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc.h"

//#define DEBUG_LED_DRIVER
#define DEBUG_DISPLAY_DRIVER

uint8_t Buffer[4] = {0xAA, 0xBB, 0xCC, 0xDD};

void power_on_self_check()
{
    soc_reset_reason_t reason = esp_rom_get_reset_reason(0);   // CPU0
//    ESP_LOGI(TAG, "Reset reason: %d", reason);

    /* 第一次上电复位后，主动再软重启一次，让 BootROM 重新采样 strapping */
//    if (reason == RESET_REASON_CHIP_POWER_ON) {
//        ESP_LOGI(TAG, "First power-on, reboot once...");
//        esp_restart();          // 立即软重启
//    }
    /* 其余复位原因（SW、WDT、DEEPSLEEP 等）直接往下走 */
}

void app_main(void)
{
    #ifdef DEBUG_DISPLAY_DRIVER
    display_config_t display_config;
    const char *file_hello = SDCARD_MOUNT_POINT"/manba.txt";
    char data[64];

    Display_Bus_Init(&display_config);
    Display_Device_Init(&display_config, DISPLAY_DEVICE_SDCARD);
    
    snprintf(data, sizeof(data), "%s %s!\n", "Hello",
             display_config.sdcard_config.sdcard_card->cid.name);
    SDcard_WriteFile(file_hello, data);
    SDcard_ReadFile(file_hello);
    #endif

    #ifdef DEBUG_LED_DRIVER
    led_config_t led_config[LED_TYPE_NUM];
    LED_Init(led_config);
    while(1)
    {
        LED_SetLevel(NORMAL_GREEN, LED_ON);
        LED_SetLevel(SLEEP_BLUE, LED_ON);
        LED_SetLevel(WARNNING_YELLOW, LED_ON);
        LED_SetLevel(ERROR_RED, LED_ON);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        LED_SetLevel(NORMAL_GREEN, LED_OFF);
        LED_SetLevel(SLEEP_BLUE, LED_OFF);
        LED_SetLevel(WARNNING_YELLOW, LED_OFF);
        LED_SetLevel(ERROR_RED, LED_OFF);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    #endif
}
