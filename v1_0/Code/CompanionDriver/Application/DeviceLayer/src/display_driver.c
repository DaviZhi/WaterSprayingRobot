#include "display_driver.h"

char* TAG = "DISPLAY_DRIVER";

void Display_Bus_Init(display_config_t *display_config)
{
    display_config->display_bus_config.sclk_io_num = DISPLAY_SPI_SCLK_PIN;
    display_config->display_bus_config.mosi_io_num = DISPLAY_SPI_MOSI_PIN;
    display_config->display_bus_config.miso_io_num = DISPLAY_SPI_MISO_PIN;
    display_config->display_bus_config.max_transfer_sz = 4092;
    display_config->display_bus_config.quadhd_io_num = -1;
    display_config->display_bus_config.quadwp_io_num = -1;
    display_config->display_bus_config.intr_flags = 0;
    spi_bus_initialize(SPI2_HOST, &display_config->display_bus_config,
                       SPI_DMA_CH_AUTO);
}

void Display_Device_Init(display_config_t *display_config, display_device_e display_device)
{
    switch(display_device)
    {
        case DISPLAY_DEVICE_ST7796U:
        {
            display_config->st7796u_config.
            st7796u_interface_config.clock_source = SPI_CLK_SRC_DEFAULT;

            display_config->st7796u_config.
            st7796u_interface_config.clock_speed_hz = 1000 * 1000 * 20; //20MHz

            display_config->st7796u_config.
            st7796u_interface_config.dummy_bits = 0;

            display_config->st7796u_config.
            st7796u_interface_config.mode = 0;

            display_config->st7796u_config.
            st7796u_interface_config.spics_io_num = ST7796U_SPI_CS_PIN;

            display_config->st7796u_config.
            st7796u_interface_config.duty_cycle_pos = 128;

            display_config->st7796u_config.
            st7796u_interface_config.post_cb = ST7796U_TransmitCpltCallBack;
            spi_bus_add_device(SPI2_HOST,
                               &display_config->st7796u_config.st7796u_interface_config,
                               &display_config->st7796u_config.st7796u_handle);
            break;
        }
        case DISPLAY_DEVICE_SDCARD:
        {
            sdspi_device_config_t sdcard_config_temp = SDSPI_DEVICE_CONFIG_DEFAULT();
            display_config->sdcard_config.sdcard_device_config = sdcard_config_temp;
            display_config->sdcard_config.sdcard_device_config.host_id = SPI2_HOST;
            display_config->sdcard_config.sdcard_device_config.gpio_cs = SDCARD_SPI_CS_PIN;

            esp_vfs_fat_mount_config_t sdcard_mount_config_temp = VFS_FAT_MOUNT_DEFAULT_CONFIG();
            display_config->sdcard_config.sdcard_mount_config = sdcard_mount_config_temp;

            display_config->sdcard_config.sdcard_mount_config.allocation_unit_size = 16 * 1024;
            display_config->sdcard_config.sdcard_mount_config.max_files = 5;
            display_config->sdcard_config.mount_point = SDCARD_MOUNT_POINT;

            sdmmc_card_t* card = &display_config->sdcard_config.sdcard_card;
            esp_vfs_fat_sdspi_mount(display_config->sdcard_config.mount_point,
                                    &display_config->sdcard_config.sdcard_host,
                                    &display_config->sdcard_config.sdcard_device_config,
                                    &display_config->sdcard_config.sdcard_mount_config,
                                    &card);
            
            sdmmc_card_print_info(stdout, &display_config->sdcard_config.sdcard_card);
            break;
        }
        case DISPLAY_DEVICE_NONE:
        break;
        default:
        break;
    }
}

void SDcard_WriteFile(const char* path, const char* data)
{
    FILE* f = fopen(path, "w");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, data);
    fclose(f);
    ESP_LOGI(TAG, "File written");
}

void SDcard_ReadFile(const char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    ESP_LOGI(TAG, "Read from file: '%s'", line);
}

void IRAM_ATTR ST7796U_TransmitCpltCallBack(spi_transaction_t* st7796u_spi_transaction)
{
//    printf("Transmit ok!");
}