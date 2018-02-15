/*
 * Relay.h
 *
 *  Created on: 8 ����. 2018 �.
 *      Author: Maksim Fedarenka
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
    void setPin(Pin *pin);

    void switchOff();
    void switchOn();
};

} /* namespace components */

#endif /* COMPONENTS_RELAY_H_ */
