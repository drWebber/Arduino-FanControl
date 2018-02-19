/*
 * Button.h
 *
 *  Created on: 18 ����. 2018 �.
 *      Author: ����
 */

#ifndef COMPONENTS_BUTTON_H_
#define COMPONENTS_BUTTON_H_

#include "Pin.h"
#include "../util/Timer.h"

namespace components {

class Button {
private:
    Pin *pin;
    util::Timer debounceTimer;
    util::Timer holdTimer;
    uint16_t holdDelay;
    bool lastState = false;
    bool prevState = false;
    bool holded = false;
    bool pressed = false;
public:
    Button(Pin *pin, uint16_t holdDelay = 1000);

    bool isPressed();
    bool isHolded();
    uint8_t getPreviousState();

    void execute();

};

} /* namespace components */

#endif /* COMPONENTS_BUTTON_H_ */
