/*
 * Sensor.cpp
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
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
