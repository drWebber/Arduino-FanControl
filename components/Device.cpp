/*
 * Device.cpp
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#include "Device.h"

namespace components {

Device::Device(Pin *pin) {
    this->pin = pin;
}

Pin* Device::getPin() {
    return pin;
}

void Device::setPin(Pin *pin) {
    this->pin = pin;
}

} /* namespace components */
