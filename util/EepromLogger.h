/*
 * Logger.h
 *
 *  Created on: 14 февр. 2018 г.
 *      Author: Макс
 */

#ifndef UTIL_EEPROMLOGGER_H_
#define UTIL_EEPROMLOGGER_H_

#include "Arduino.h"
#include <EEPROM.h>
namespace util {

class EepromLogger {
private:
	uint8_t min = 0;
	uint8_t max = 0;
	uint8_t minValIndex;
	uint8_t maxValIndex;
	uint8_t lastValIndex;
public:
    EepromLogger(uint16_t startIndex, uint8_t capacity);
    virtual ~EepromLogger();

	uint8_t getMin() const;
	uint8_t getMax() const;

	void writeMin(uint8_t min);
	void writeMax(uint8_t max);
	void writeValue(uint8_t index, uint8_t value) const;
	void zeroFill();

	void printLog() const;
};

} /* namespace util */

#endif /* UTIL_EEPROMLOGGER_H_ */
