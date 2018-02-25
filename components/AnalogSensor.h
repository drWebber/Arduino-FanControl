/*
 * Sensor.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Maksim Fedarenka
 */

#ifndef COMPONENTS_ANALOGSENSOR_H_
#define COMPONENTS_ANALOGSENSOR_H_

#include "Pin.h"
#include "Device.h"

namespace components {

class AnalogSensor : public Device {
private:
    uint16_t threshold;
public:
    AnalogSensor(Pin *pin, uint16_t threshold);
    virtual ~AnalogSensor();
    void setThreshold(uint16_t threshold);

    virtual bool isAboveValue();
    virtual bool isBelowValue();
    virtual uint16_t read();
};

} /* namespace components */

#endif /* COMPONENTS_ANALOGSENSOR_H_ */
