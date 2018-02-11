#include "timer.h"

void Timer::setSecondsInterval(int seconds)
{
    this->interval = seconds * 1000;
}

void Timer::setMinutesInterval(int minutes)
{
    this->interval = minutes * 60 * 1000;
}

boolean Timer::isTimeOut()
{
    if (millis() > nextEvent) {
        nextEvent = millis() + interval;
        return true;
    }
    return false;
}
