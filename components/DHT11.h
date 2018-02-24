/*
 * DHT11.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Maksim Fedarenka
 */

#ifndef COMPONENTS_DHT11_H_
#define COMPONENTS_DHT11_H_

#include "Pin.h"
#include "../util/Timer.h"

using namespace util;

namespace components {

class DHT11 {
private:
    Pin *pin = NULL;
    uint8_t temperature = 0;
    uint8_t humidity = 0;
    uint8_t temperatureThreshold = 0;
    uint8_t humidityThreshold = 0;
    util::Timer measurmentsDelay;
    util::Timer *delay18 = NULL;
    bool error = true;
    bool testDevice(uint8_t value);
public:
    DHT11(Pin *dhtPin, uint8_t delay);

    void execute();
    uint8_t getHumidity() const;
    uint8_t getTemperature() const;
    void setHumidityThreshold(uint8_t humidityThreshold);
    void setTemperatureThreshold(uint8_t temperatureThreshold);

    bool isAboveValue();
    bool isBelowValue();
    bool isError();
};

} /* namespace components */

#endif /* COMPONENTS_DHT11_H_ */
