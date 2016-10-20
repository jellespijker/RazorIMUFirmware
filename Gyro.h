//
// Created by peer23peer on 10/18/16.
//

#include "Types.h"
#include "Sensor.h"

#include <Wire.h>
#include <Arduino.h>

#pragma once

class Gyro : public Sensor {
public:
    Gyro();

    ~Gyro();

    virtual void read() override;
};

