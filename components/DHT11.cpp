#include "DHT11.h"

namespace components {

DHT11::DHT11(Pin *dhtPin) {
    this->pin = dhtPin;
}

uint8_t DHT11::getHumidity() const {
    return humidity;
}

uint8_t DHT11::getTemperature() const {
    return temperature;
}

uint8_t DHT11::read() {
    byte data[40];

    pin->setOutputMode();
    pin->setLow();
    delay(18);

    pin->setHigh();
    delayMicroseconds(40);
    pin->setInputMode();

    if (!testDevice(LOW)) return false;

    if (!testDevice(HIGH)) return false;

    unsigned long time;
    for (int i = 0; i < 40; i++) {
        if (!testDevice(LOW)) return false;

        time = micros();
        if (!testDevice(HIGH)) return false;

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
    if (bytes[4] != sum) return false;

    humidity    = bytes[0];
    temperature = bytes[2];

    return true;
}

bool DHT11::testDevice(char value) {
    short timeout = 10000;
    while (pin->dlRead() == value)
        if (timeout-- == 0) return false;
    return true;
}

bool DHT11::isAboveValue() {
    return !isBelowValue();
}

bool DHT11::isBelowValue() {
    if (temperature <= temperatureThreshold && humidity <= humidityThreshold) {
        return true;
    }
    return false;
}

void DHT11::setHumidityThreshold(uint8_t humidityThreshold) {
    this->humidityThreshold = humidityThreshold;
}

void DHT11::setTemperatureThreshold(uint8_t temperatureThreshold) {
    this->temperatureThreshold = temperatureThreshold;
}

} /* namespace components */
