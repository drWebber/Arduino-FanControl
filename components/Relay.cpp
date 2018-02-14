/*
 * Relay.cpp
 *
 *  Created on: 8 ����. 2018 �.
 *      Author: ����
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

void Relay::switchOff() {
    pin->setHigh();
}

void Relay::switchOn() {
    pin->setLow();
}

} /* namespace components */
