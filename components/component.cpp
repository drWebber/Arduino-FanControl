#include "Component.h"

Component::Component()
{

}

int Component::getDataPin()
{
    return dataPin;
}

void Component::setDataPin(int dataPin, uint8_t mode)
{
    this->dataPin = dataPin;
    pinMode(dataPin, mode);
}