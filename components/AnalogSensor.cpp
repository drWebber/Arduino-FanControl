/*
 * Sensor.cpp
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#include "AnalogSensor.h"

namespace components {

components::AnalogSensor::AnalogSensor(Pin *dhtPin, int threshold) {
    this->pin = dhtPin;
    this->threshold = threshold;
}

void AnalogSensor::setThreshold(short threshold) {
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

short AnalogSensor::read() {
    return pin->agRead();
}

} /* namespace components */
