/*
 * Mq2.h
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_MQ2_H_
#define COMPONENTS_MQ2_H_

#include "DigitalSensor.h"

namespace components {

class Mq2: public DigitalSensor {
private:
    bool warmedUp = false;
public:
    Mq2(Pin *pin) : DigitalSensor(pin) { };
    uint8_t read();
    bool isWarmedUp();
};

} /* namespace components */

#endif /* COMPONENTS_MQ2_H_ */
