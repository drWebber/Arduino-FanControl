/*
 * Logger.cpp
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: ����
 */

#include "EepromLogger.h"

namespace util {

EepromLogger::EepromLogger(uint16_t startIndex, int16_t size,
        uint8_t objectSize) {
    minValIndex = startIndex;
    maxValIndex = minValIndex + objectSize;
    nextIndex = maxValIndex + objectSize;
    lastValIndex = startIndex + (size * objectSize);
    int16_t tmpMmin = EEPROM.read(minValIndex);
    int16_t tmpMax = EEPROM.read(maxValIndex);
    if (tmpMmin == tmpMax) {
        minimum = INT16_MAX;
        maximum = INT16_MIN;
    } else {
        minimum = tmpMmin;
        maximum = tmpMax;
    }
    this->objectSize = objectSize;
}

int16_t EepromLogger::getMin() const {
    return minimum;
}

int16_t EepromLogger::getMax() const {
    return maximum;
}

EepromLogger::~EepromLogger() {
    // TODO Auto-generated destructor stub
}

void EepromLogger::writeMin(int16_t minimum) {
    this->minimum = minimum;
    EEPROM.put(minValIndex, minimum);
}

void EepromLogger::writeMax(int16_t maximum) {
    this->maximum = maximum;
    EEPROM.put(maxValIndex, maximum);
}

void EepromLogger::writeNextValue(int16_t value) {
    if (nextIndex < lastValIndex) {
        EEPROM.put(nextIndex, value);
        nextIndex += objectSize;
    }
}

void EepromLogger::printLog() const {
    int16_t val = 0;
    Serial.print("Min value: ");
    val = EEPROM.get(minValIndex, val);
    Serial.println(val);
    Serial.print("Max value: ");
    val = EEPROM.get(maxValIndex, val);
    Serial.println(val);
}

void EepromLogger::clearLog() {
    for (int16_t i = minValIndex; i < lastValIndex; ++i) {
        EEPROM.write(i, 0);
    }
    maximum = INT16_MIN;
    minimum = INT16_MAX;
}

void EepromLogger::clearChangesLog() {
    int16_t indx = maxValIndex + objectSize;
    nextIndex = indx;
    for (int16_t i = indx; i < lastValIndex; ++i) {
        EEPROM.write(i, 0);
    }
}

void EepromLogger::printChangesLog() const {
    int16_t val = 0;
    for (int16_t i = (maxValIndex + objectSize); i < lastValIndex;
            i += objectSize) {
        EEPROM.get(i, val);
        Serial.print(val);
        Serial.print(" ");
    }
    Serial.println();
}

} /* namespace util */
