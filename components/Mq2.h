/*
 * Mq2.h
 *
 *  Created on: 24 февр. 2018 г.
 *      Author: Макс
 */

#ifndef COMPONENTS_MQ2_H_
#define COMPONENTS_MQ2_H_

#include "DigitalSensor.h"
#include "../util/Timer.h"

using namespace util;

namespace components {

class Mq2: public DigitalSensor {
private:
    bool warmedUp = false;
    bool prevState = false;
    Timer *debounceTimer = NULL;
public:
    Mq2(Pin *pin) : DigitalSensor(pin) { };
    bool read();
    bool isWarmedUp();
};

} /* namespace components */

#endif /* COMPONENTS_MQ2_H_ */
