/*
 * Fan.h
 *
 *  Created on: 8 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_FAN_H_
#define COMPONENTS_FAN_H_

#include "AnalogSensor.h"
#include "Relay.h"
#include "DHT11.h"
#include "../util/Timer.h"

namespace components {

class Fan {
private:
    Relay *relay = NULL;
    bool turnedOn = false;
    Timer *timer = NULL;
public:
    Fan(Relay *relay);
    virtual ~Fan();
    void setRelay(const Relay *relay);

    void turnOn(short minutes);
    void turnOff();

    bool isTurnedOn();

    Timer *getTimer();
};

} /* namespace components */

#endif /* COMPONENTS_FAN_H_ */
