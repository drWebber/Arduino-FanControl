#ifndef COMPONENTS_TIMER_H
#define COMPONENTS_TIMER_H

#include <Arduino.h>

namespace util {

class Timer
{
private:
    unsigned long interval = 0;
    unsigned long nextEvent = 0;
public:
    Timer() {};
    void setSecondsInterval(uint8_t seconds);
    void setMinutesInterval(uint8_t minutes);
    bool isTimeOut();
};

} /* namespace util */

#endif // COMPONENTS_TIMER_H
