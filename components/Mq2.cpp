/*
 * Mq2.cpp
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#include "Mq2.h"

namespace components {

uint8_t components::Mq2::read() {
    return !pin->dlRead();
}

bool components::Mq2::isWarmedUp() {
    if (!warmedUp) {
        warmedUp = !this->read();
    }
    return warmedUp;
}

} /* namespace components */
