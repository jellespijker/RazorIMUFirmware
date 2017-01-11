//
// Created by peer23peer on 10/18/16.
//
#pragma once

#include "Types.h"
#include "Sensor.h"

#include <Wire.h>
#include <Arduino.h>

class Accel : public Sensor {
public:
    Accel();

    ~Accel();

    virtual void read() override;

    void SpeedProfile(uint8_t profile);
private:
    float mg = 0.049;
};
