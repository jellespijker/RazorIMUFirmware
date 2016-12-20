#include "Magn.h"

Magn::Magn()
        : Sensor(MAGN_ADDRESS) {
    const byte contMode[2] = {0x02, 0x00};
    const byte sampleRate[2] = {0x00, 0b00011000};
    send(contMode, 2); // Set continuous mode (default 10 Hz)
    delay(5);
    send(sampleRate, 2); // Set 50 Hz
    delay(5);
}

Magn::~Magn() {

}

void Magn::read() {
    uint8_t buffer[6];
    if (request(buffer, 6, 0x03)) {
        xyz_[0] = -1 * (int16_t) (((((uint16_t) buffer[4]) << 8) | buffer[5]));  // X axis (internal sensor -y axis)
        xyz_[1] = -1 * (int16_t) (((((uint16_t) buffer[0]) << 8) | buffer[1]));  // Y axis (internal sensor -x axis)
        xyz_[2] = -1 * (int16_t) (((((uint16_t) buffer[2]) << 8) | buffer[3]));  // Z axis (internal sensor -z axis)
    }
    //TODO error handling if read error
}