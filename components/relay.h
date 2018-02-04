#ifndef RELAY_H
#define RELAY_H

#include "component.h"
#include <Arduino.h>

class Relay :
    public Component
{
public:
    Relay();
    void swithcOn();
    void swithcOff();
	boolean isSwithcedOn();
private:
	boolean state;
};

#endif // RELAY_H
