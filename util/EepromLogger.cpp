/*
 * Logger.cpp
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: ����
 */

#include "EepromLogger.h"

namespace util {

EepromLogger::EepromLogger(uint16_t startIndex, int16_t size) {
    minValIndex = startIndex;
    maxValIndex = minValIndex + 1;
    nextIndex = maxValIndex + 1;
    lastValIndex = startIndex + size;
    int16_t tmpMax = EEPROM.read(maxValIndex);
    int16_t tmpMmin = EEPROM.read(minValIndex);
    if (tmpMmin == tmpMax) {
        minimum = INT16_MAX;
        maximum = INT16_MIN;
    } else {
        minimum = tmpMmin;
        maximum = tmpMax;
    }
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
    EEPROM.write(minValIndex, minimum);
}

void EepromLogger::writeMax(int16_t maximum) {
    this->maximum = maximum;
    EEPROM.write(maxValIndex, maximum);
}

void EepromLogger::writeNextValue(int16_t value) {
    if (nextIndex < lastValIndex) {
        EEPROM.write(nextIndex, value);
        nextIndex++;
    }
}

void EepromLogger::printLog() const {
    Serial.print("Min value: ");
    Serial.println(EEPROM.read(minValIndex));
    Serial.print("Max value: ");
    Serial.println(EEPROM.read(maxValIndex));
}

void EepromLogger::clearLog() {
    for (int16_t i = minValIndex; i < lastValIndex; ++i) {
        EEPROM.write(i, 0);
    }
}

void EepromLogger::clearChangesLog() {
    int8_t indx = maxValIndex + 1;
    nextIndex = indx;
    for (int16_t i = indx; i < lastValIndex; ++i) {
        EEPROM.write(i, 0);
    }
}

void EepromLogger::printChangesLog() const {
    int8_t indx = maxValIndex + 1;
    for (int16_t i = indx; i < lastValIndex; ++i) {
        Serial.print(EEPROM.read(i));
        Serial.print(" ");
    }
    Serial.println();
}

} /* namespace util */
