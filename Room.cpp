/*
 * Room.cpp
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
 */

#include "Room.h"

namespace components {

Room::Room() {
    // TODO Auto-generated constructor stub

}

Room::~Room() {
    // TODO Auto-generated destructor stub
}

void Room::setDht(const DHT11* dht) {
    this->dht = dht;
}

void Room::setLightSensor(const AnalogSensor* lightSensor) {
    this->lightSensor = lightSensor;
}

void Room::setMqSensor(const AnalogSensor* mqSensor) {
    this->mqSensor = mqSensor;
}

void Room::setFan(const Fan *fan) {
    this->fan = fan;
}

void Room::serve() {
    /* fan serving */
    airCheck();
}

void Room::airCheck() {
    if (fan != NULL) {
        if (fan->isTurnedOn()) {
            Serial.println("The fan is turned on"); //TODO debug
            if (fan->getTimer()->isTimeOut()) {
                Serial.println("Time out"); //TODO debug
                if (!isRequiredVentilation()) {
                    fan->turnOff();
                } else {
                    Serial.println("It's needed more time"); //TODO debug
                    fan->getTimer()->setMinutesInterval(3);
                }
            }
        } else {
            if (lightSensor->isBelowValue()) {
                Serial.println("Light is detected"); //TODO debug
                if (isRequiredVentilation()) {
                    fan->turnOn(1); //TODO изменить время вентиляции
                }
            } else {
                Serial.println("Light isn't detected"); //TODO debug
            }
        }
    }
}

bool Room::isRequiredVentilation() {
    if (dht != NULL) {
        if (dht->read()) {
            if (dht->isAboveValue()) {
                Serial.println("Air is overheated or too wet"); //TODO debug
                Serial.print("Temperature: "); //TODO debug
                Serial.println(dht->getTemperature()); //TODO debug
                Serial.print("Humidity: "); //TODO debug
                Serial.println(dht->getHumidity()); //TODO debug
                return true;
            }
        }
    } else if (mqSensor->isAboveValue()) {
        Serial.println("Cigarette smoke is detected"); //TODO debug
        return true;
    }
    Serial.println("Ventilation is not required"); //TODO debug
    return false;
}

const DHT11 *Room::getDht() const {
	return dht;
}

const AnalogSensor *Room::getLightSensor() const {
	return lightSensor;
}

const AnalogSensor *Room::getMqSensor() const {
	return mqSensor;
}

} /* namespace components */
