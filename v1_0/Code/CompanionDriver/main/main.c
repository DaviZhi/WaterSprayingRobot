#include <stdio.h>
#include <string.h>
#include "comp_driver_ver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "display_driver.h"

uint8_t Buffer[4] = {0xAA, 0xBB, 0xCC, 0xDD};

display_config_t display_config;

void app_main(void)
{
    const char *file_hello = SDCARD_MOUNT_POINT"/hello.txt";
    char data[64];

    Display_Bus_Init(&display_config);
    Display_Device_Init(&display_config, DISPLAY_DEVICE_SDCARD);
    
    snprintf(data, sizeof(data), "%s %s!\n", "Hello",
             display_config.sdcard_config.sdcard_card.cid.name);
    SDcard_WriteFile(file_hello, data);
    SDcard_ReadFile(file_hello);
    while(1)
    {
        ;
    }
}
