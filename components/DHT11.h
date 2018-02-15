/*
 * DHT11.h
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: Maksim Fedarenka
 */

#ifndef COMPONENTS_DHT11_H_
#define COMPONENTS_DHT11_H_

#include "Pin.h"

namespace components {

class DHT11 {
private:
    Pin *pin = NULL;
    uint8_t temperature = 0;
    uint8_t humidity = 0;
    bool testDevice(char value);
    uint8_t temperatureThreshold = 0;
    uint8_t humidityThreshold = 0;
public:
    DHT11(Pin *dhtPin);

    uint8_t read();
    uint8_t getHumidity() const;
    uint8_t getTemperature() const;
    void setHumidityThreshold(uint8_t humidityThreshold);
    void setTemperatureThreshold(uint8_t temperatureThreshold);

    bool isAboveValue();
    bool isBelowValue();
};

} /* namespace components */

#endif /* COMPONENTS_DHT11_H_ */
