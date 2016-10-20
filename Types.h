//
// Created by peer23peer on 10/18/16.
//
#pragma once

// Sensor I2C addresses
#define ACCEL_ADDRESS ((int16_t) 0x53) // 0x53 = 0xA6 / 2
#define MAGN_ADDRESS  ((int16_t) 0x1E) // 0x1E = 0x3C / 2
#define GYRO_ADDRESS  ((int16_t) 0x68) // 0x68 = 0xD0 / 2
#define OUTPUT__BAUD_RATE 115200
#define STATUS_LED_PIN 13

#define byte uint8_t

//#define DEBUG

#ifdef DEBUG
#define DMSG(x)  Serial.println(x)
#else
#define DMSG(x)
#endif

