/*
 * Sensor.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_ANALOGSENSOR_H_
#define COMPONENTS_ANALOGSENSOR_H_

#include "Pin.h"


namespace components {

class AnalogSensor {
private:
    Pin *pin;
    int threshold;
public:
    AnalogSensor(Pin *dhtPin, int threshold);
    virtual ~AnalogSensor();
    const Pin *getPin() const;
    void setPin(const Pin *pin);
    void setThreshold(short threshold);

    virtual bool isAboveValue();
    virtual bool isBelowValue();
    virtual short read();
};

} /* namespace components */

#endif /* COMPONENTS_ANALOGSENSOR_H_ */
