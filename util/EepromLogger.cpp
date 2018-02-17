/*
 * Logger.cpp
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: ����
 */

#include "EepromLogger.h"

namespace util {

EepromLogger::EepromLogger(uint16_t startIndex, int16_t size,
        uint8_t objectSize, uint16_t eepromCapacity) {
    minValIndex = startIndex;
    maxValIndex = minValIndex + objectSize;
    nextIndex = maxValIndex + objectSize;
    lastValIndex = startIndex + (size * objectSize);
    if (lastValIndex > eepromCapacity - 1) {
        Serial.println("EepromLogger::EepromLogger ERROR");
        Serial.println("The eeprom memory has lower capacity, than you need!!! "
                "The data couldn't be properly stored. "
                "Some data would be lost");
        lastValIndex = eepromCapacity - 1;
    }
    int16_t tmpMmin, tmpMax = 0;
    EEPROM.get(minValIndex, tmpMmin);
    EEPROM.get(maxValIndex, tmpMax);
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
    int16_t val = INT16_MIN;
    Serial.print("Min value: ");
    EEPROM.get(minValIndex, val);
    Serial.println(val);
    Serial.print("Max value: ");
    EEPROM.get(maxValIndex, val);
    Serial.println(val);
}

void EepromLogger::clearLog() {
    for (int16_t i = minValIndex; i < lastValIndex; ++i) {
        EEPROM.update(i, 0);
    }
    minimum = INT16_MAX;
    maximum = INT16_MIN;
}

void EepromLogger::clearChangesLog() {
    int16_t indx = maxValIndex + objectSize;
    nextIndex = indx;
    for (int16_t i = indx; i < lastValIndex; ++i) {
        EEPROM.update(i, 0);
    }
}

void EepromLogger::printChangesLog() const {
    int16_t val = INT16_MIN;
    for (int16_t i = (maxValIndex + objectSize); i < lastValIndex;
            i += objectSize) {
        EEPROM.get(i, val);
        Serial.print(val);
        Serial.print(" ");
    }
    Serial.println();
}

} /* namespace util */
