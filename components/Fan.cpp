/*
 * Fan.cpp
 *
 *  Created on: 8 февр. 2018 г.
 *      Author: Макс
 */

#include "Fan.h"

namespace components {

Fan::Fan(Relay *relay) {
    this->relay = relay;
}

void Fan::setDht(const DHT11 *dht) {
    this->dht = dht;
}

void Fan::setLightSensor(const AnalogSensor *lightSensor) {
    this->lightSensor = lightSensor;
}

void Fan::setMqSensor(const AnalogSensor *mqSensor) {
    this->mqSensor = mqSensor;
}

void Fan::setRelay(const Relay *relay) {
    this->relay = relay;
}

Fan::~Fan() {
    // TODO Auto-generated destructor stub
}

void Fan::serve() {
    if (isTurnedOn) {
        Serial.println("The fan is turned on"); //TODO debug
        if (timer->isTimeOut()) {
            Serial.println("Time out"); //TODO debug
            if (!isRequireVentilation()) {
                turnOff();
            } else {
                Serial.println("It's needed more time"); //TODO debug
                timer->setMinutesInterval(3);
            }
        }
    } else {
        if (lightSensor->isBelowValue()) {
            Serial.println("Light is detected"); //TODO debug
            if (isRequireVentilation()) {
                turnOn(1); //TODO изменить время вентиляции
            }
        } else {
            Serial.println("Light isn't detected"); //TODO debug
        }
    }
}

bool Fan::isRequireVentilation() {
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

void Fan::turnOn(short minutes) {
    Serial.println("Fan is turned on"); //TODO debug
    isTurnedOn = true;
    relay->turnOn();
    timer = new Timer();
    timer->setMinutesInterval(minutes);
}

void Fan::turnOff() {
    Serial.println("Fan is turned off"); //TODO debug
    relay->turnOff();
    timer = NULL;
    isTurnedOn = false;
}

} /* namespace components */
