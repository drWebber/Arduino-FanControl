#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
public:
    Timer();
    void setSecondsInterval(int seconds);
    void setMinutesInterval(int minutes);
    boolean isTimeOut();
private:
    unsigned long interval;
    unsigned long nextEvent;
};

#endif // TIMER_H
