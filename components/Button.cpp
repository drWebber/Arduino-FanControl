/*
 * Button.cpp
 *
 *  Created on: 18 февр. 2018 г.
 *      Author: Макс
 */

#include "Button.h"

namespace components {

Button::Button(Pin* pin, uint16_t holdDelay) {
    this->pin = pin;
    this->holdDelay = holdDelay;
    pin->setInputPullupMode();
    debounceTimer.setMillisecondsInterval(10);
    holdTimer.setMillisecondsInterval(0);
}

bool Button::isPressed() {
    return pressed;
}

uint8_t Button::getPreviousState() {
    return prevState;
}

bool Button::isHolded() {
    return holded;
}

void Button::execute() {
    if (holdTimer.getMillisecondsInterval() == 0) {
        holdTimer.setMillisecondsInterval(holdDelay);
    }

    if (debounceTimer.isTimeOut()) {
        bool currentState = !pin->dlRead();

        if (!currentState && lastState && !holded) {
            pressed = true;
            prevState = !prevState;
        } else if (!currentState && lastState && holded) {
            holded = false;
        }

        if (holdTimer.isTimeOut() && currentState && lastState && !pressed) {
            holded = true;
        }

        if (!holded  && !currentState) {
            holdTimer.setMillisecondsInterval(holdDelay);
        }

        lastState = currentState;
    } else {
        pressed = false;
    }
}

} /* namespace components */
