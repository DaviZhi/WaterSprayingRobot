#include "st7796u_driver.h"
#include "st7796u_xdefine.h"

void ST7796U_Init(st7796u_config_t *st7796u_config)
{
    st7796u_config->st7796u_spi_bus_config.sclk_io_num = ST7796U_SPI_SCLK_PIN;
    st7796u_config->st7796u_spi_bus_config.mosi_io_num = ST7796U_SPI_MOSI_PIN;
    st7796u_config->st7796u_spi_bus_config.miso_io_num = ST7796U_SPI_MISO_PIN;
    st7796u_config->st7796u_spi_bus_config.max_transfer_sz = 4092;
    st7796u_config->st7796u_spi_bus_config.quadhd_io_num = -1;
    st7796u_config->st7796u_spi_bus_config.quadwp_io_num = -1;
    st7796u_config->st7796u_spi_bus_config.isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO;
    st7796u_config->st7796u_spi_bus_config.intr_flags = 0;
    spi_bus_initialize(SPI2_HOST, &st7796u_config->st7796u_spi_bus_config,
                       SPI_DMA_CH_AUTO);

    st7796u_config->st7796u_spi_device_config.clock_source = SPI_CLK_SRC_DEFAULT;
    st7796u_config->st7796u_spi_device_config.clock_speed_hz = SPI_MASTER_FREQ_20M;
    st7796u_config->st7796u_spi_device_config.dummy_bits = 0;
    st7796u_config->st7796u_spi_device_config.mode = 0;
    st7796u_config->st7796u_spi_device_config.spics_io_num = ST7796U_SPI_CS_PIN;
    st7796u_config->st7796u_spi_device_config.duty_cycle_pos = 128;
    st7796u_config->st7796u_spi_device_config.post_cb = ST7796U_TransmitCpltCallBack;
    spi_bus_add_device(SPI2_HOST, &st7796u_config->st7796u_spi_device_config,
                       &st7796u_config->st7796u_spi_handle);
}

void ST7796U_TransmitCpltCallBack(spi_transaction_t* st7796u_spi_transaction)
{
    printf("Transmit ok!");
}