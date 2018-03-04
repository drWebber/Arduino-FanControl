/*
 * Mq2.cpp
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#include "Mq2.h"

namespace components {

bool components::Mq2::read() {
    bool state = !pin->dlRead();
    if (state) {
        if (debounceTimer == NULL) {
            debounceTimer = new Timer();
            debounceTimer->setMillisecondsInterval(250);
        }
        if (debounceTimer->isTimeOut()) {
            if (prevState && state) {
                prevState = false;
                delete debounceTimer;
                debounceTimer = NULL;
                return true;
            } else {
                prevState = state;
            }
        }
    } else {
        if (debounceTimer != NULL) {
            delete debounceTimer;
            debounceTimer = NULL;
        }
        prevState = false;
    }
    return false;
}

bool components::Mq2::isWarmedUp() {
    if (!warmedUp) {
        warmedUp = !this->read();
    }
    return warmedUp;
}

} /* namespace components */
