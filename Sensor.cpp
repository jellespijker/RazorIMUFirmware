//
// Created by peer23peer on 10/18/16.
//

#include "Sensor.h"
#include "Types.h"

Sensor::Sensor(int16_t addr)
        : addr_(addr) {

}

float *Sensor::getXYZ() {
    return xyz_;
}

void Sensor::send(const byte *data, uint8_t size) {
    Wire.beginTransmission(addr_);
    for (uint8_t i = 0; i < size; i++) {
        Wire.write(data[i]);
    }
    Wire.endTransmission();
}

bool Sensor::request(uint8_t *buffer, uint8_t size, byte addr) {
    uint8_t i = 0;

    send(&addr, 1);

    Wire.beginTransmission(addr_);
    Wire.requestFrom(addr_, size);
    delay(5);
    while (Wire.available()) {
        buffer[i++] = Wire.read();
    }
    Wire.endTransmission();
    if (i != size) {
        return false;
    }
    return true;
}

Sensor::~Sensor() {

}
