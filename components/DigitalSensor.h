/*
 * DigitalSensor.h
 *
 *  Created on: 24 ����. 2018 �.
 *      Author: ����
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
