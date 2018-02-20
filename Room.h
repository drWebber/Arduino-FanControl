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
#include "components/Button.h"

namespace components {

class Room {
private:
    DHT11 *dht = NULL;
    AnalogSensor *mqSensor = NULL;
    AnalogSensor *lightSensor = NULL;
    Fan *fan = NULL;
    Button *fanCtrlBtn = NULL;

    bool isRequiredVentilation();
    void airCheck();
public:
    void setDht(DHT11 *dht);
    void setLightSensor(AnalogSensor *lightSensor);
    void setMqSensor(AnalogSensor *mqSensor);
    void setFan(Fan *fan);
    void setFanControlButton(Button *btn);

    void serve();
	DHT11 *getDht() const;
	AnalogSensor *getLightSensor() const;
	AnalogSensor *getMqSensor() const;
};

} /* namespace components */

#endif /* ROOM_H_ */
