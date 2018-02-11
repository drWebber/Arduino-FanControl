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
    DHT11 *dht = NULL;
    AnalogSensor *mqSensor = NULL;
    AnalogSensor *lightSensor = NULL;
    bool isTurnedOn = false;
    Timer *timer = NULL;

    void turnOn(short minutes);
    void turnOff();
    bool isRequireVentilation();
public:
    Fan(Relay *relay);
    virtual ~Fan();
    void setDht(const DHT11 *dht);
    void setLightSensor(const AnalogSensor *lightSensor);
    void setMqSensor(const AnalogSensor *mqSensor);
    void setRelay(const Relay *relay);

    void serve();
};

} /* namespace components */

#endif /* COMPONENTS_FAN_H_ */
