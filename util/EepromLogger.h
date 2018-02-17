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

/*
    Класс для логгирования показаний датчиков в памяти EEPROM.
    Atmega 328 имеет 1Кб памяти, которая хранится по 1 байту под индексами
    от 0 до 1023.
    Ячейка startIndex предназначена для хранения минимально зафиксированного
    за все вермя логгирования значения, ячейка startIndex + 1, соответственно
    максимального значения. Остальные свободные ячейки предназначены для
    хранения истории изменений показаний датчика (кол-во зависит от capacity)

    startIndex - начальный индекс для сохранения логов, выбирать АККУРАТНО,
    чтобы не затереть чужие логи!

    capacity - кол-во отведенных под хранение ячеек памяти, в методе writeValue
    используется относительная система исчисления, при выходе за вместимость
    данные записываться не будут.
*/

class EepromLogger {
private:
    int16_t minimum = INT16_MAX;
	int16_t maximum = INT16_MIN;
	int16_t minValIndex;
	int16_t maxValIndex;
	int16_t lastValIndex;
	int16_t nextIndex;
public:
    EepromLogger(uint16_t startIndex, int16_t capacity);
    virtual ~EepromLogger();

    int16_t getMin() const;
    int16_t getMax() const;

	/* запись минимально зафиксированного значения */
	void writeMin(int16_t minimum);
	/* запись максимально зафиксированного значения */
	void writeMax(int16_t maximum);
    /* запись значения в историю изменений
     */
	void writeNextValue(int16_t value);
	/* очистить весь лог */
	void clearLog();
    /* очистить историю изменений */
	void clearChangesLog();

	/* Вывести в Serial мин. и макс. зафиксированные значения */
	void printLog() const;
	/* Вывести в Serial историю изменений поступающих в логгер значений */
	void printChangesLog() const;
};

} /* namespace util */

#endif /* UTIL_EEPROMLOGGER_H_ */
