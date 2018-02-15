/*
 * Logger.cpp
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
 */

#include "EepromLogger.h"

namespace util {

EepromLogger::EepromLogger(uint16_t startIndex, uint8_t size) {
	minValIndex = startIndex;
	maxValIndex = minValIndex + 1;
	lastValIndex = startIndex + size;
}

uint8_t EepromLogger::getMin() const {
	return min;
}

uint8_t EepromLogger::getMax() const {
	return max;
}

EepromLogger::~EepromLogger() {
    // TODO Auto-generated destructor stub
}

void EepromLogger::writeMin(uint8_t min) {
	this->min = min;
	EEPROM.write(minValIndex, min);
}

void EepromLogger::writeMax(uint8_t max) {
	this->max = max;
	EEPROM.write(maxValIndex, max);
}

void EepromLogger::writeValue(uint8_t refIndex, uint8_t value) const {
	EEPROM.write(maxValIndex + refIndex + 1, value);
}

void EepromLogger::zeroFill() {
	for (uint8_t i = minValIndex; i < lastValIndex; ++i) {
		EEPROM[i] = 0;
	}
}

void EepromLogger::printLog() const {
	Serial.print("Min value: ");
	Serial.println(EEPROM.read(minValIndex));
	Serial.print("Max value: ");
	Serial.println(EEPROM.read(maxValIndex));
	for (uint8_t i = maxValIndex + 1; i < lastValIndex; ++i) {
		Serial.print(" value: ");
		Serial.println(EEPROM.read(i));
	}
}

} /* namespace util */
