/*
 * Pin.cpp
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: ����
 */
#include "Pin.h"

namespace components {

Pin::Pin(uint8_t index, uint8_t mode) {
    this->index = index;
    if (mode != INPUT) {
        setOutputMode();
    }
}

Pin::~Pin() {

}

void Pin::setHigh() {
    digitalWrite(index, HIGH);
}

void Pin::setLow() {
    digitalWrite(index, LOW);
}

void Pin::setValue(uint8_t value) {
    analogWrite(index, value);
}

uint8_t Pin::dlRead() {
    return digitalRead(index);
}

uint16_t Pin::agRead() {
    return analogRead(index);
}

void Pin::setOutputMode() {
    pinMode(index, OUTPUT);
}

void Pin::setInputMode() {
    pinMode(index, INPUT);
}

void Pin::setInputPullupMode() {
    pinMode(index, INPUT_PULLUP);
}

} /* namespace components */
