/*
 * Relay.h
 *
 *  Created on: 8 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_RELAY_H_
#define COMPONENTS_RELAY_H_

#include "Pin.h"

namespace components {

class Relay {
private:
    Pin *pin;
public:
    Relay(Pin *pin);
    virtual ~Relay();
    const Pin *getPin() const;
    void setPin(const Pin *pin);

    void turnOff();
    void turnOn();
};

} /* namespace components */

#endif /* COMPONENTS_RELAY_H_ */
