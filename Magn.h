//
// Created by peer23peer on 10/18/16.
//
#pragma once

#include "Types.h"
#include "Sensor.h"
#include <Wire.h>
#include <Arduino.h>

class Magn : public Sensor {
public:
    Magn();

    ~Magn();

    virtual void read() override;

};
