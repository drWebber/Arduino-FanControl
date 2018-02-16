#include "Fan.h"

namespace components {

Fan::Fan(Relay *relay) {
    this->relay = relay;
}

void Fan::setRelay(Relay *relay) {
    this->relay = relay;
}

Fan::~Fan() {
    // TODO Auto-generated destructor stub
}

util::Timer *Fan::getTimer() {
    return timer;
}

void Fan::turnOn(uint8_t minutes) {
    Serial.println("Fan is turned on"); //TODO debug
    turnedOn = true;
    relay->switchOn();
    timer = new util::Timer();
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
