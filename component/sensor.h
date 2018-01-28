#ifndef SENSOR_H
#define SENSOR_H

#include "component.h"
#include <Arduino.h>

class Sensor :
	public Component
{
public:
    Sensor();
    void setEventThreshold(int threshold);
    boolean isEvent();
private:
    int eventThreshold;
};

#endif // SENSOR_H
