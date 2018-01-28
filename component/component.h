#ifndef Component_H
#define Component_H

#include <Arduino.h>

class Component
{
public:
    Component();
	int getDataPin();
    void setDataPin(int dataPin, uint8_t mode);
protected:
    int dataPin;
};

#endif // Component_H
