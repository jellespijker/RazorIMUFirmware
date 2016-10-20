//
// Created by peer23peer on 10/18/16.
//

#pragma once

#include <Wire.h>
#include <Arduino.h>

class Sensor {
public:
    Sensor(int16_t addr);

    ~Sensor();

    virtual void read() = 0;

    float *getXYZ();

protected:
    float xyz_[3];
    const int16_t addr_;

    void send(const byte *data, uint8_t size);

    bool request(uint8_t *buffer, uint8_t size, byte addr);
};

