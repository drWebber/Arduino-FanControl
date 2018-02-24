/*
 * Button.cpp
 *
 *  Created on: 18 ����. 2018 �.
 *      Author: ����
 */

#include "Button.h"

namespace components {

Button::Button(Pin* pin, uint16_t holdDelay) {
    this->pin = pin;
    this->holdDelay = holdDelay;
    pin->setInputPullupMode();
    debounceTimer.setMillisecondsInterval(20);
    holdTimer.setMillisecondsInterval(holdDelay);
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
