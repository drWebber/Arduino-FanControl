/*
 * ValueLogger.h
 *
 *  Created on: 16 февр. 2018 г.
 *      Author: Maksim Fedarenka
 */

#ifndef UTIL_VALUEWATCHER_H_
#define UTIL_VALUEWATCHER_H_

#include "EepromLogger.h"
#include "Timer.h"

using namespace util;

namespace util {

enum LogType {VALUE_FALLING, VALUE_RISING};

/*
 * Служит для отслеживания изменений логгируемых значений (показаний датчиков
 * и т.п.).
 * Локальный максимум/минимум фиксируется, если приходящее значение
 * больше/меньше сохраненного в логгере максимального/минимального значения
 * После фиксации локального максимума/минимума история изменения значений
 * логгера очищается, новые значения фиксируются по таймеру, с интервалом в
 * logInterval секунд.
 *
 * logger - пока только EepromLogger (в дальнейшем возможно будет интерфейс
 * Logger, под SdCardLogger и т.п.) для сохранения данных.
 * logInterval - интервал в секундах для настройки таймера фиксации изменений
 * приходящих значений.
 * logType - тип сохранения истории приходящих значений  может быть выбран:
 * VALUE_FALLING для сохранения истории падения значений после локального
 * масимума;
 * VALUE_RISING для сохранения роста значений после локального минимума
 *
 * Например: фиксируется локальный максимум в 21С, при выбранном типе
 * логгирования VALUE_FALLING будем сохранять историю падения значений после
 * достижения масимума (например сработает охладитель). После фиксации максимума
 * сохраненная история одноразово очищается. Последующие приходящие значения
 * сохраняются по таймеру, определенному по logInterval (в секундах).
 * Т.е. итоговый лог может быть таким:
 * 1: 21C
 * 2: 20C
 * ...
 * n: xxC
 */

class ValueWatcher {
private:
	EepromLogger *logger;
	uint8_t logInterval;
	Timer *timer = NULL;
	LogType logType;
	bool localMaximum = false;
	bool localMinimum = false;
	int16_t prevVal = 0;
public:
	ValueWatcher(EepromLogger *logger, uint8_t logInterval = 30,
	        LogType logType = VALUE_FALLING);
	virtual ~ValueWatcher();

	uint8_t getLogInterval() const;
	void setLogInterval(uint8_t logInterval);

	/* Принимает текущее значение currentValue, проверяет, является ли оно:
	 * зафиксированным минимумом и масимумом;
	 * по достижении макс или мин значений (в зависимости от logType) сохраняет
	 * по таймеру историю изменений
	 */
	void log(int16_t currentValue);
};

} /* namespace util */

#endif /* UTIL_VALUEWATCHER_H_ */
