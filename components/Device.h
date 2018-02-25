/*
 * Device.h
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_DEVICE_H_
#define COMPONENTS_DEVICE_H_

#include "Pin.h"

namespace components {

class Device {
protected:
    Pin *pin = NULL;
public:
    Device(Pin *pin);
    Pin *getPin();
    void setPin(Pin *pin);
};

} /* namespace components */

#endif /* COMPONENTS_DEVICE_H_ */
