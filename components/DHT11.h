/*
 * DHT11.h
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_DHT11_H_
#define COMPONENTS_DHT11_H_

#include <Arduino.h>
#include "Sensor.h"

namespace components {

class DHT11: public Sensor {
private:
    char temperature;
    char humidity;
    bool testDevice(char value);
public:
    DHT11(Pin &dhtPin, int threshold);
    short read();
    short getHumidity() const;
    short getTemperature() const;
};

} /* namespace components */

#endif /* COMPONENTS_DHT11_H_ */
