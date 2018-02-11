#include "timer.h"

namespace components {

void Timer::setSecondsInterval(short seconds)
{
    this->interval = seconds * 1000;
    nextEvent = millis() + interval;
}

void Timer::setMinutesInterval(short minutes)
{
    interval = minutes * 60000;
    nextEvent = millis() + interval;
}

boolean Timer::isTimeOut()
{
    if (millis() > nextEvent) {
        nextEvent = millis() + interval;
        return true;
    }
    return false;
}

} /* namespace components */
