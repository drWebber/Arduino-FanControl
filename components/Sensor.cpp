/*
 * Sensor.cpp
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#include "Sensor.h"

namespace components {

components::Sensor::Sensor(Pin *dhtPin, int threshold) {
    this->pin = dhtPin;
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
    return read() <= threshold;
}

const Pin *Sensor::getPin() const {
    return pin;
}

void Sensor::setPin(const Pin *pin) {
    this->pin = pin;
}

short Sensor::read() {
    return pin->agRead();
}

} /* namespace components */
