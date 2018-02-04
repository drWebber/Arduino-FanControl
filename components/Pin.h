/*
 * Pin.h
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: ����
 */

#include <Arduino.h>

#ifndef COMPONENTS_PIN_H_
#define COMPONENTS_PIN_H_

namespace components {

class Pin {
private:
    char index;
public:
    Pin();
    Pin(char index, char mode = INPUT);
    virtual ~Pin();
    void setOutputMode();
    void setInputMode();

    void setHigh();
    void setLow();
    void setValue(int value);

    char dlRead();
    int agRead();
};

} /* namespace components */

#endif /* COMPONENTS_PIN_H_ */
