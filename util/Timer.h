#ifndef COMPONENTS_TIMER_H
#define COMPONENTS_TIMER_H

#include <Arduino.h>

namespace components {

class Timer
{
private:
    unsigned long interval = 0;
    unsigned long nextEvent = 0;
public:
    Timer() {};
    void setSecondsInterval(short seconds);
    void setMinutesInterval(short minutes);
    boolean isTimeOut();
};

} /* namespace components */

#endif // COMPONENTS_TIMER_H
