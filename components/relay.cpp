#include "relay.h"

Relay::Relay()
{
}

void Relay::swithcOn()
{
	state = true;
    digitalWrite(dataPin, HIGH);
}

void Relay::swithcOff()
{
	state = false;
    digitalWrite(dataPin, LOW);
}

boolean Relay::isSwithcedOn()
{
    return state;
}
