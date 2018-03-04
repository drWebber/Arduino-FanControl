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

Mq2 *Room::getMqSensor() const {
    return mqSensor;
}

void Room::setMqSensor(Mq2* mqSensor) {
    this->mqSensor = mqSensor;
}

void Room::setFan(Fan *fan) {
    this->fan = fan;
}

void Room::setFanControlButton(Button* btn) {
    this->fanCtrlBtn = btn;
}

void Room::serve() {
    if (fanCtrlBtn != NULL) {
        if (fanCtrlBtn->isPressed()) {
            Serial.println("isPressed fan switched on");
            fan->turnOn(3); // TODO изменить время вентиляции
        }
        if (fanCtrlBtn->isHolded()) {
            fan->turnOff();
        }
    }
    airCheck();
}

void Room::airCheck() {
    if (fan != NULL) {
        if (fan->isTurnedOn()) {
            if (fan->getTimer()->isTimeOut()) {
                if (!isRequiredVentilation()) {
                    fan->turnOff();
                } else {
                    fan->getTimer()->setMinutesInterval(3); //TODO изменить время вентиляции
                }
            }
        } else {
            if (lightSensor->isBelowValue()) {
                if (isRequiredVentilation()) {
                    fan->turnOn(3); //TODO изменить время вентиляции
                }
            }
        }
    }
}

bool Room::isRequiredVentilation() {
    if (dht != NULL) {
        if (!dht->isError()) {
            if (dht->isAboveValue()) {
                Serial.println("Air is overheated or too wet");
                return true;
            }
        }
    }
    if (mqSensor->isWarmedUp()) {
        if (mqSensor->read()) {
            Serial.println("Cigarette smoke is detected");
            return true;
        }
    }
    return false;
}

DHT11 *Room::getDht() const {
	return dht;
}

AnalogSensor *Room::getLightSensor() const {
	return lightSensor;
}

} /* namespace components */
