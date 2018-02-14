/*
 * Room.h
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: ����
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "components/AnalogSensor.h"
#include "components/DHT11.h"
#include "components/Fan.h"

namespace components {

class Room {
private:
    DHT11 *dht = NULL;
    AnalogSensor *mqSensor = NULL;
    AnalogSensor *lightSensor = NULL;
    Fan *fan = NULL;

    bool isRequiredVentilation();
    void airCheck();
public:
    Room();
    virtual ~Room();

    void setDht(const DHT11 *dht);
    void setLightSensor(const AnalogSensor *lightSensor);
    void setMqSensor(const AnalogSensor *mqSensor);
    void setFan(const Fan *fan);

    void serve();
};

} /* namespace components */

#endif /* ROOM_H_ */
