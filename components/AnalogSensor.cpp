/*
 * Sensor.cpp
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#include "AnalogSensor.h"

namespace components {

components::AnalogSensor::AnalogSensor(Pin *dhtPin, uint16_t threshold) {
    this->pin = dhtPin;
    this->threshold = threshold;
}

void AnalogSensor::setThreshold(uint16_t threshold) {
    this->threshold = threshold;
}

AnalogSensor::~AnalogSensor() {
    // TODO Auto-generated destructor stub
}

bool AnalogSensor::isAboveValue() {
    return !isBelowValue();
}

bool AnalogSensor::isBelowValue() {
    return read() <= threshold;
}

const Pin *AnalogSensor::getPin() const {
    return pin;
}

void AnalogSensor::setPin(const Pin *pin) {
    this->pin = pin;
}

uint16_t AnalogSensor::read() {
    return pin->agRead();
}

} /* namespace components */
