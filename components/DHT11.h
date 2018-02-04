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
    float temperature;
    float humidity;
public:
    DHT11(Pin pin, int threshold);
    int read();
    float getHumidity() const;
    float getTemperature() const;
};

} /* namespace components */

#endif /* COMPONENTS_DHT11_H_ */
