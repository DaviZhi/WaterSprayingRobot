idf_component_register(SRCS "src/display_driver.c"
                            "src/led_driver.c"
                            "src/buzzer_driver.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES "esp_driver_spi"
                                "esp_driver_gpio"
                                "esp_driver_sdspi"
                                "esp_driver_sdmmc"
                                "fatfs")