/*
 * DHT11.cpp
 *
 *  Created on: 4 ����. 2018 �.
 *      Author: ����
 */

#include "DHT11.h"
#include "exceptions/TimeoutException.h"
#include "exceptions/ChecksumException.h"

namespace components {

} /* namespace components */

float components::DHT11::getHumidity() const {
    return humidity;
}

float components::DHT11::getTemperature() const {
    return temperature;
}

int components::DHT11::read() {
    byte data[40];

    pin.setOutputMode();
    pin.setLow();
    delay(18);

    pin.setHigh();
    delayMicroseconds(40);
    pin.setInputMode();

    short timeout = 10000;
    while (pin.dlRead() == LOW)
        if (timeout-- == 0) throw new TimeoutException();

    timeout = 10000;
    while (pin.dlRead() == HIGH)
        if (timeout-- == 0) throw TimeoutException();

    unsigned long time;
    for (int i = 0; i < 40; i++) {
        timeout = 10000;
        while (pin.dlRead() == LOW)
              if (timeout-- == 0) throw TimeoutException();

        time = micros();
        timeout = 10000;
        while (pin.dlRead() == HIGH)
              if (timeout-- == 0) throw TimeoutException();

        if ((micros() - time) > 40) {
            data[i] = 1;
        } else {
            data[i] = 0;
        }
    }

    byte bytes[5] = {0, 0, 0, 0, 0};
    int byteindex = 0;
    int posindex = 7;
    for (int i = 0; i < 40; i++) {
        if (data[i] == 1)  bytes[byteindex] |= (1 << posindex);
        posindex--;
        if (posindex < 0) {
            posindex = 7;
            byteindex++;
        }
    }

    unsigned short sum = bytes[0] + bytes[2];
    if (bytes[4] != sum) throw ChecksumException();

    humidity    = bytes[0];
    temperature = bytes[2];
}
