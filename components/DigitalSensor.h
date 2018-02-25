/*
 * DigitalSensor.h
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "Device.h"

namespace components {

class DigitalSensor: public Device {
public:
    DigitalSensor(Pin *pin) : Device(pin) { };
    virtual ~DigitalSensor() {};
    virtual uint8_t read();
};

} /* namespace components */

#endif /* DIGITALSENSOR_H_ */
