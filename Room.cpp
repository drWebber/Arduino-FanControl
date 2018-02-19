/*
 * Room.cpp
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
 */

#include "Room.h"

namespace components {

void Room::setDht(DHT11* dht) {
    this->dht = dht;
}

void Room::setLightSensor(AnalogSensor* lightSensor) {
    this->lightSensor = lightSensor;
}

void Room::setMqSensor(AnalogSensor* mqSensor) {
    this->mqSensor = mqSensor;
}

void Room::setFan(Fan *fan) {
    this->fan = fan;
}

void Room::serve() {
    /* fan serving */
    airCheck();
}

void Room::airCheck() {
    if (fan != NULL) {
        if (fan->isTurnedOn()) {
            if (fan->getTimer()->isTimeOut()) {
                if (!isRequiredVentilation()) {
                    fan->turnOff();
                } else {
                    fan->getTimer()->setMinutesInterval(3);
                }
            }
        } else {
            if (lightSensor->isBelowValue()) {
                if (isRequiredVentilation()) {
                    fan->turnOn(1); //TODO изменить время вентиляции
                }
            }
        }
    }
}

bool Room::isRequiredVentilation() {
    if (dht != NULL) {
        if (dht->read()) {
            if (dht->isAboveValue()) {
                return true;
            }
        }
    }
    if (mqSensor->isAboveValue()) {
        return true;
    }
    return false;
}

DHT11 *Room::getDht() const {
	return dht;
}

AnalogSensor *Room::getLightSensor() const {
	return lightSensor;
}

AnalogSensor *Room::getMqSensor() const {
	return mqSensor;
}

} /* namespace components */
