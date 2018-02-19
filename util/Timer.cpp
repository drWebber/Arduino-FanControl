#include "Timer.h"

namespace util {

void Timer::setSecondsInterval(uint8_t seconds)
{
    this->interval = seconds * 1000;
    nextEvent = millis() + interval;
}

void Timer::setMinutesInterval(uint8_t minutes)
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

} /* namespace util */
