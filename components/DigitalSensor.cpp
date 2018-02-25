/*
 * DigitalSensor.cpp
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#include "DigitalSensor.h"

namespace components {

uint8_t components::DigitalSensor::read() {
    return pin->dlRead();
}

} /* namespace components */



