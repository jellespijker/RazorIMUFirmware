//
// Created by peer23peer on 10/18/16.
//

#include "Accel.h"

Accel::Accel()
        : Sensor::Sensor(ACCEL_ADDRESS) {
    const byte powReg[2] = {0x2D, 0x08};
    const byte fullRes[2] = {0x31, 0x08};
    const byte normOp[2] = {0x2C, 0x09};
    send(powReg, 2); // Set power register Measurement mode
    delay(5);
    send(fullRes, 2); // Set Data format register to full resolution
    delay(5);
    send(normOp, 2); // Set to 50Hz, normal operation
    delay(5);
}

Accel::~Accel() {

}

void Accel::read() {
    int i = 0;
    uint8_t buffer[6];
    if (request(buffer, 6, 0x32)) {
        xyz_[0] = (int16_t) ((((uint16_t) buffer[3]) << 8) | buffer[2]);  // X axis (internal sensor y axis)
        xyz_[1] = (int16_t) ((((uint16_t) buffer[1]) << 8) | buffer[0]);  // Y axis (internal sensor x axis)
        xyz_[2] = (int16_t) ((((uint16_t) buffer[5]) << 8) | buffer[4]);  // Z axis (internal sensor z axis)
    }
    //TODO error handling if read error
}
