#ifndef ST7796U_DRIVER_H
#define ST7796U_DRIVER_H

#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "driver/gpio.h"

typedef enum
{
    ST7796U_MADCTL_MY  = 0x80,  // Row Address Order
    ST7796U_MADCTL_MX  = 0x40,  // Column Address Order
    ST7796U_MADCTL_MV  = 0x20,  // Row/Column Exchange
    ST7796U_MADCTL_ML  = 0x10,  // Vertical Refresh Order
    ST7796U_MADCTL_BGR = 0x08,  // RGB-BGR ORDER
    ST7796U_MADCTL_RGB = 0x00,
    ST7796U_MADCTL_MH  = 0x04,  // Horizontal Refresh Order
    ST7796U_NOP        = 0x00,  // No Operation
    ST7796U_SWRESET    = 0x01,  // Software reset
    ST7796U_RDDID      = 0x04,  // Read Display ID
    ST7796U_RDNUMED    = 0x05,  // Read Number of the Errors on DSI
    ST7796U_RDDST      = 0x09,  // Read Display Status
    ST7796U_RDDPM      = 0x0A,  // Read Display Power Mode
    ST7796U_RDDMADCTL  = 0x0B,  // Read Display MADCTL
    ST7796U_RDDCOLMOD  = 0x0C,  // Read Display Pixel Format
    ST7796U_RDDIM      = 0x0D,  // Read Display Image Mode
    ST7796U_RDDSM      = 0x0E,  // Read Display Signal Status
    ST7796U_RDDSDR     = 0x0F,  // Read Display Self-Diagnostic Result
    ST7796U_SLPIN      = 0x10,  // Sleep In
    ST7796U_SLPOUT     = 0x11,  // Sleep Out
    ST7796U_PTLON      = 0x12,  // Partial Display Mode On
    ST7796U_NORON      = 0x13,  // Normal Display Mode On
    ST7796U_INVOFF     = 0x20,  // Display Inversion Off
    ST7796U_INVON      = 0x21,  // Display Inversion On
    ST7796U_DISPOFF    = 0x28,  // Display Off
    ST7796U_DISPON     = 0x29,  // Display On
    ST7796U_CASET      = 0x2A,  // Column Address Set
    ST7796U_RASET      = 0x2B,  // Row Address Set
    ST7796U_RAMWR      = 0x2C,  // Memory Write
    ST7796U_RAMRD      = 0x2E,  // Memory Read
    ST7796U_PTLAR      = 0x30,  // Partial Area
    ST7796U_VSCRDEF    = 0x33,  // Vertical Scrolling Definition
    ST7796U_TEOFF      = 0x34,  // Tearing Effect Line OFF
    ST7796U_TEON       = 0x35,  // Tearing Effect Line On
    ST7796U_MADCTL     = 0x36,  // Memory Data Access Control
    ST7796U_VSCSAD     = 0x37,  // Vertical Scroll Start Address of RAM
    ST7796U_IDMOFF     = 0x38,  // Idle Mode Off
    ST7796U_IDMON      = 0x39,  // Idle Mode On
    ST7796U_COLMOD     = 0x3A,  // Interface Pixel Format
    ST7796U_WRMEMC     = 0x3C,  // Write Memory Continue
    ST7796U_RDMEMC     = 0x3E,  // Read Memory Continue
    ST7796U_STE        = 0x44,  // Set Tear ScanLine
    ST7796U_GSCAN      = 0x45,  // Get ScanLine
    ST7796U_WRDISBV    = 0x51,  // Write Display Brightness
    ST7796U_RDDISBV    = 0x52,  // Read Display Brightness Value
    ST7796U_WRCTRLD    = 0x53,  // Write CTRL Display
    ST7796U_RDCTRLD    = 0x54,  // Read CTRL value Display
    ST7796U_WRCABC     = 0x55,  // Write Adaptive Brightness Control
    ST7796U_RDCABC     = 0x56,  // Read Content Adaptive Brightness Control
    ST7796U_WRCABCMB   = 0x5E,  // Write CABC Minimum Brightness
    ST7796U_RDCABCMB   = 0x5F,  // Read CABC Minimum Brightness
    ST7796U_RDFCS      = 0xAA,  // Read First Checksum
    ST7796U_RDCFCS     = 0xAF,  // Read Continue Checksum
    ST7796U_RDID1      = 0xDA,  // Read ID1
    ST7796U_RDID2      = 0xDB,  // Read ID2
    ST7796U_RDID3      = 0xDC,  // Read ID3
    ST7796U_IFMODE     = 0xB0,  // Interface Mode Control
    ST7796U_FRMCTR1    = 0xB1,  // Frame Rate Control (In Normal Mode/Full Colors)
    ST7796U_FRMCTR2    = 0xB2,  // Frame Rate Control 2 (In Idle Mode/8 colors)
    ST7796U_FRMCTR3    = 0xB3,  // Frame Rate Control 3(In Partial Mode/Full Colors)
    ST7796U_DIC        = 0xB4,  // Display Inversion Control
    ST7796U_BPC        = 0xB5,  // Blanking Porch Control
    ST7796U_DFC        = 0xB6,  // Display Function Control
    ST7796U_EM         = 0xB7,  // Entry Mode Set
    ST7796U_PWR1       = 0xC0,  // Power Control 1
    ST7796U_PWR2       = 0xC1,  // Power Control 2
    ST7796U_PWR3       = 0xC2,  // Power Control 3
    ST7796U_VCMPCTL    = 0xC5,  // VCOM Control
    ST7796U_VCMOST     = 0xC6,  // VCOM Offset Register
    ST7796U_NVMADW     = 0xD0,  // NVM Address/Data Write
    ST7796U_NVMBPROG   = 0xD1,  // NVM Byte Program
    ST7796U_NVMSTRD    = 0xD2,  // NVM Status Read
    ST7796U_RDID4      = 0xD3,  // Read ID4
    ST7796U_PGC        = 0xE0,  // Positive Gamma Control
    ST7796U_NGC        = 0xE1,  // Negative Gamma Control
    ST7796U_DGC1       = 0xE2,  // Digital Gamma Control 1
    ST7796U_DGC2       = 0xE3,  // Digital Gamma Control 2
    ST7796U_DOCA       = 0xE8,  // Display Output Ctrl Adjust
    ST7796U_CSCON      = 0xF0,  // Command Set Control
    ST7796U_SPIRC      = 0xFB,  // SPI Read Control

} st7796u_reg_e;

typedef struct 
{
    spi_device_handle_t st7796u_spi_handle;  //SPI device handle
    spi_device_interface_config_t st7796u_spi_device_config; //SPI device configuration
    spi_bus_config_t st7796u_spi_bus_config; //SPI bus configuration
}st7796u_config_t;

void ST7796U_Init(st7796u_config_t* st7796u_config);
void ST7796U_TransmitCpltCallBack(spi_transaction_t* st7796u_spi_transaction);

#endif