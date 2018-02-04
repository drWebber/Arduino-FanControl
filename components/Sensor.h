/*
 * Sensor.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_SENSOR_H_
#define COMPONENTS_SENSOR_H_

#include "Pin.h"


namespace components {

class Sensor {
private:
    int threshold;
protected:
    Pin pin;
public:
    Sensor(Pin pin, int threshold);
    virtual ~Sensor();
    const Pin& getPin() const;
    void setPin(const Pin& pin);
    void setThreshold(int threshold);

    bool isAboveValue();
    bool isBelowValue();
    virtual int read();
};

} /* namespace components */

#endif /* COMPONENTS_SENSOR_H_ */
