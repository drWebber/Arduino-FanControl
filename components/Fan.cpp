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

void Fan::setRelay(const Relay *relay) {
    this->relay = relay;
}

Fan::~Fan() {
    // TODO Auto-generated destructor stub
}

Timer *Fan::getTimer() {
    return timer;
}

void Fan::turnOn(short minutes) {
    Serial.println("Fan is turned on"); //TODO debug
    turnedOn = true;
    relay->switchOn();
    timer = new Timer();
    timer->setMinutesInterval(minutes);
}

void Fan::turnOff() {
    Serial.println("Fan is turned off"); //TODO debug
    relay->switchOff();
    timer = NULL;
    turnedOn = false;
}

bool Fan::isTurnedOn() {
    return turnedOn;
}

} /* namespace components */
