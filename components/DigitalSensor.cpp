/*
 * DigitalSensor.cpp
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#include "DigitalSensor.h"

namespace components {

bool components::DigitalSensor::read() {
    return pin->dlRead();
}

} /* namespace components */



