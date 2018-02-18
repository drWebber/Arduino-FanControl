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

void Timer::setMillisecondsInterval(uint16_t milliSeconds) {
    this->interval = milliSeconds;
    nextEvent = millis() + interval;
}

unsigned long Timer::getMillisecondsInterval() {
    return interval;
}

bool Timer::isTimeOut()
{
    if (millis() > nextEvent) {
        nextEvent = millis() + interval;
        return true;
    }
    return false;
}

} /* namespace util */
