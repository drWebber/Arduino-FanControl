/*
 * Pin.cpp
 *
 *  Created on: 4 февр. 2018 г.
 *      Author: Макс
 */
#include "Pin.h"

namespace components {

Pin::Pin(char index, char mode) {
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

void Pin::setValue(int value) {
    analogWrite(index, value);
}

char Pin::dlRead() {
    return digitalRead(index);
}

void Pin::setOutputMode() {
    pinMode(index, OUTPUT);
}

void Pin::setInputMode() {
    pinMode(index, INPUT);
}

int Pin::agRead() {
    return analogRead(index);
}

} /* namespace components */
