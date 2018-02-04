#include "sensor.h"

Sensor::Sensor()
{

}

void Sensor::setEventThreshold(int threshold)
{
    this->eventThreshold = threshold;
}

boolean Sensor::isEvent()
{
    if (analogRead(dataPin) < eventThreshold) {
		return true;
	}
	return false;
}
