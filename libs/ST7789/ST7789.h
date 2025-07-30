#pragma once

#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <cstdlib>

void sendCommand(uint8_t cmd);

void sendData(uint8_t data);

void resetDisplay();

void initST7789();

void setAddrWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end);

void pushColor(uint16_t color);

void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void showBuf(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *buffer);