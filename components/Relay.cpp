/*
 * Relay.cpp
 *
 *  Created on: 8 февр. 2018 г.
 *      Author: Макс
 */

#include "Relay.h"

namespace components {

components::Relay::Relay(Pin *pin) {
    this->pin = pin;
    pin->setOutputMode();
    pin->setHigh();
}

const Pin *Relay::getPin() const {
    return pin;
}

void Relay::setPin(const Pin *pin) {
    this->pin = pin;
}

Relay::~Relay() {
    // TODO Auto-generated destructor stub
}

void Relay::turnOff() {
    pin->setLow();
}

void Relay::turnOn() {
    pin->setHigh();
}

} /* namespace components */
