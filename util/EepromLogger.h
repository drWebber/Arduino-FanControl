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
    чтобы не затереть чужие логи! При расчете УЧИТЫВАТЬ objectSize * capacity
    предыдущих логгеров!

    capacity - кол-во отведенных под хранение ячеек памяти, в методе writeValue
    используется относительная система исчисления, при выходе за вместимость
    данные записываться не будут. Выбирать с учетом objectSize и остаточной
    вместимости EEPROM.

    objectSize - размер одного сохраняемого объекта в байтах. Одна ячейка
    EEPROM равна 1 байту, для хранения 2 и более байт нужно занять несколько
    ячеек! Например, для хранения int16_t, необходимо (есессно) передать двойку
    в этом параметре.

    eepromCapacity - размер EEPROM памяти, для atmega328 это 1024 байта.
*/

class EepromLogger {
private:
    int16_t minimum = INT16_MAX;
	int16_t maximum = INT16_MIN;
	uint16_t minValIndex;
	uint16_t maxValIndex;
	uint16_t lastValIndex;
	uint16_t nextIndex;
	uint16_t objectSize;
public:
    EepromLogger(uint16_t startIndex, int16_t capacity, uint8_t objectSize,
            uint16_t eepromCapacity);
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
