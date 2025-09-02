idf_component_register(SRCS "src/st7796u_driver.c" "src/led_driver.c" "src/buzzer_driver.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES "esp_driver_spi" "esp_driver_gpio")