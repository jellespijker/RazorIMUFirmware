//
// Created by peer23peer on 10/18/16.
//

#include "Gyro.h"

Gyro::Gyro()
        : Sensor(GYRO_ADDRESS) {
    const byte powerUp[2] = {0x3E, 0x80};
    const byte fullScale[2] = {0x16, 0x1B};
    const byte sampleRate[2] = {0x15, 0x0A};
    const byte pll[2] = {0x3E, 0x00};
    send(powerUp, 2); // Power up reset defaults
    delay(5);
    send(fullScale, 2); // Select full-scale range of the gyro sensors Set LP filter bandwidth to 42 Hz
    delay(5);
    send(sampleRate, 2); // Set sample rate to 50 Hz
    delay(5);
    send(pll, 2); // Set clock to PLL with z gyro reference
    delay(5);
}

Gyro::~Gyro() {

}

void Gyro::read() {
    uint8_t buffer[6];
    if (request(buffer, 6, 0x1D)) {
        xyz_[0] = -1 * (int16_t) (((((uint16_t) buffer[2]) << 8) | buffer[3]));    // X axis (internal sensor -y axis)
        xyz_[1] = -1 * (int16_t) (((((uint16_t) buffer[0]) << 8) | buffer[1]));    // Y axis (internal sensor -x axis)
        xyz_[2] = -1 * (int16_t) (((((uint16_t) buffer[4]) << 8) | buffer[5]));    // Z axis (internal sensor -z axis)
    }
}