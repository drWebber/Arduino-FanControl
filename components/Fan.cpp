#include "Fan.h"

namespace components {

Fan::Fan(Relay *relay) {
    this->relay = relay;
}

void Fan::setRelay(Relay *relay) {
    this->relay = relay;
}

util::Timer *Fan::getTimer() {
    return timer;
}

void Fan::turnOn(uint8_t minutes) {
    turnedOn = true;
    relay->switchOn();
    timer = new util::Timer();
    timer->setMinutesInterval(minutes);
}

void Fan::turnOff() {
    relay->switchOff();
    delete timer;
    timer = NULL;
    turnedOn = false;
}

bool Fan::isTurnedOn() {
    return turnedOn;
}

} /* namespace components */
