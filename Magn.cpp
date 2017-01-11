#include "Magn.h"

Magn::Magn()
        : Sensor(MAGN_ADDRESS) {
    const byte contMode[2] = {0x02, 0x00};
    const byte sampleRate[2] = {0x00, 0b01111000};
    const byte gainMode[2] = {0x01, 0b11100000};
    send(contMode, 2); // Set continuous mode (default 10 Hz)
    delay(5);
    send(sampleRate, 2); // Set 75 Hz with 8 point moving average
    delay(5);
    send(gainMode, 2); // Set to +/- 1.9 Ga LSb/Gaus = 820 Digital Resolution mG/LSb = 1.22
    delay(5);
}

Magn::~Magn() {

}

void Magn::read() {
    uint8_t buffer[6];
    if (request(buffer, 6, 0x03)) {
        xyz_[0] = static_cast<float>((-1 * (int16_t) (((((uint16_t) buffer[0]) << 8) | buffer[1]))))*0.435f;  // Y axis in mTesla
        xyz_[2] = static_cast<float>((-1 * (int16_t) (((((uint16_t) buffer[2]) << 8) | buffer[3]))))*0.435;  // Z axis in mTesla
        xyz_[1] = static_cast<float>((-1 * (int16_t) (((((uint16_t) buffer[4]) << 8) | buffer[5]))))*0.435f;  // X axis in mTesla
    }
    //TODO error handling if read error
}