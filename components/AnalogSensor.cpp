/*
 * Sensor.cpp
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: ����
 */

#include "AnalogSensor.h"

namespace components {

AnalogSensor::AnalogSensor(Pin* pin, uint16_t threshold) : Device(pin) {
    this->threshold = threshold;
}

void AnalogSensor::setThreshold(uint16_t threshold) {
    this->threshold = threshold;
}

bool AnalogSensor::isAboveValue() {
    return !isBelowValue();
}

bool AnalogSensor::isBelowValue() {
    return read() <= threshold;
}

AnalogSensor::~AnalogSensor() {
}

uint16_t AnalogSensor::read() {
    return pin->agRead();
}

} /* namespace components */
