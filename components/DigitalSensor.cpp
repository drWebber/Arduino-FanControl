/*
 * DigitalSensor.cpp
 *
 *  Created on: 24 ����. 2018 �.
 *      Author: ����
 */

#include "DigitalSensor.h"

namespace components {

uint8_t components::DigitalSensor::read() {
    return pin->dlRead();
}

} /* namespace components */



