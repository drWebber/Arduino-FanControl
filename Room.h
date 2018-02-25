/*
 * Room.h
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "components/AnalogSensor.h"
#include "components/Mq2.h"
#include "components/DHT11.h"
#include "components/Fan.h"
#include "components/Button.h"

namespace components {

class Room {
private:
    DHT11 *dht = NULL;
    Mq2 *mqSensor = NULL;
    AnalogSensor *lightSensor = NULL;
    Fan *fan = NULL;
    Button *fanCtrlBtn = NULL;

    bool isRequiredVentilation();
    void airCheck();
public:
    void setDht(DHT11 *dht);
    void setLightSensor(AnalogSensor *lightSensor);
    void setMqSensor(Mq2 *mqSensor);
    void setFan(Fan *fan);
    void setFanControlButton(Button *btn);

    void serve();
	DHT11 *getDht() const;
	AnalogSensor *getLightSensor() const;
	Mq2 *getMqSensor() const;
};

} /* namespace components */

#endif /* ROOM_H_ */
