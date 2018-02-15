/*
 * Relay.h
 *
 *  Created on: 8 февр. 2018 г.
 *      Author: Maksim Fedarenka
 */

#include <Arduino.h>

#ifndef COMPONENTS_PIN_H_
#define COMPONENTS_PIN_H_

namespace components {

class Pin {
private:
	uint8_t index = 0;
public:
    Pin();
    Pin(uint8_t index, uint8_t mode = INPUT);
    virtual ~Pin();
    void setOutputMode();
    void setInputMode();

    void setHigh();
    void setLow();
    void setValue(uint8_t value);

    uint8_t dlRead();
    uint16_t agRead();
};

} /* namespace components */

#endif /* COMPONENTS_PIN_H_ */
