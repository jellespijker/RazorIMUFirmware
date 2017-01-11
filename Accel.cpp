//
// Created by peer23peer on 10/18/16.
//

#include "Accel.h"

Accel::Accel()
        : Sensor::Sensor(ACCEL_ADDRESS) {
    const byte powReg[2] = {0x2D, 0x08};
    const byte normOp[2] = {0x2C, 0x09};
    send(powReg, 2); // Set power register Measurement mode
    delay(5);
    SpeedProfile(1);
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
        xyz_[0] = ((int16_t) ((((uint16_t) buffer[1]) << 8) | buffer[0])) * mg;  // X axis (internal sensor x axis)
        xyz_[1] = ((int16_t) ((((uint16_t) buffer[3]) << 8) | buffer[2])) * mg;  // Y axis (internal sensor y axis)
        xyz_[2] = ((int16_t) ((((uint16_t) buffer[5]) << 8) | buffer[4])) * mg;  // Z axis (internal sensor z axis)
    }
    //TODO error handling if read error
}

void Accel::SpeedProfile(uint8_t profile) {
    byte range[2] = {0x31, 0b00000000}; // +/- 2g (default value)
    switch (profile) {
        //TODO test scale factor at different ranges (+/- 2g is within error)
        case 1:
            range[1] = 0b00000001; // +/- 4g
            mg = 1;
            break;
        case 2:
            range[1] = 0b00000010; // +/- 8g
            mg = 15.6/1000;
            break;
        case 3:
            range[1] = 0b00000011; // +/- 16g
            mg = 31.2/1000;
            break;
        default:
            range[1] = 0b00000000; // +/- 2g
            break;
            mg = 4.9/1000;
            break;
    }
    send(range, 2); // Set range register
    delay(5);
}
