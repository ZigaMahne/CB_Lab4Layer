#!/bin/bash
sed -i "s/WIFI_ISM43362_SPI_DRV_NUM           0/WIFI_ISM43362_SPI_DRV_NUM           $ARDUINO_SPI_NUMBER/" "RTE/CMSIS_Driver/WiFi_ISM43362_Config.h"
