/*
 * Sensor.cpp
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: ����
 */

#include "Sensor.h"

namespace components {

Sensor::Sensor(Pin pin, int threshold) {
    this->pin = pin;
    this->threshold = threshold;
}

void Sensor::setThreshold(int threshold) {
    this->threshold = threshold;
}

Sensor::~Sensor() {
    // TODO Auto-generated destructor stub
}

bool Sensor::isAboveValue() {
    return read() > threshold;
}

bool Sensor::isBelowValue() {
    return read() < threshold;
}

const Pin& Sensor::getPin() const {
    return pin;
}

void Sensor::setPin(const Pin& pin) {
    this->pin = pin;
}

int Sensor::read() {
    return pin.agRead();
}

} /* namespace components */
