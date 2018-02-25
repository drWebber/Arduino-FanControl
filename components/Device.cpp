/*
 * Device.cpp
 *
 *  Created on: 24 ����. 2018 �.
 *      Author: ����
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
