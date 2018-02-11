/*
 * DHT11.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_DHT11_H_
#define COMPONENTS_DHT11_H_

#include <Arduino.h>
#include "Pin.h"

namespace components {

class DHT11 {
private:
    Pin *pin = NULL;
    char temperature = 0;
    char humidity = 0;
    bool testDevice(char value);
    char temperatureThreshold = 0;
    char humidityThreshold = 0;
public:
    DHT11(Pin *dhtPin);

    short read();
    short getHumidity() const;
    short getTemperature() const;
    void setHumidityThreshold(char humidityThreshold);
    void setTemperatureThreshold(char temperatureThreshold);

    bool isAboveValue();
    bool isBelowValue();
};

} /* namespace components */

#endif /* COMPONENTS_DHT11_H_ */
