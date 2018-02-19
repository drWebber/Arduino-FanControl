#include "Timer.h"

namespace util {

void Timer::setSecondsInterval(uint8_t seconds)
{
    interval = static_cast<unsigned long>(seconds) * 1000;
    nextEvent = millis() + interval;
}

void Timer::setMinutesInterval(uint8_t minutes)
{
    interval = static_cast<unsigned long>(minutes) * 60000;
    nextEvent = millis() + interval;
}

void Timer::setMillisecondsInterval(uint16_t milliSeconds) {
    interval = static_cast<unsigned long>(milliSeconds);
    nextEvent = millis() + interval;
}

unsigned long Timer::getInterval() {
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
