/*
 * Room.h
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
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

    void setDht(DHT11 *dht);
    void setLightSensor(AnalogSensor *lightSensor);
    void setMqSensor(AnalogSensor *mqSensor);
    void setFan(Fan *fan);

    void serve();
	const DHT11 *getDht() const;
	const AnalogSensor *getLightSensor() const;
	const AnalogSensor *getMqSensor() const;
};

} /* namespace components */

#endif /* ROOM_H_ */
