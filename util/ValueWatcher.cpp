/*
 * ValueLogger.cpp
 *
 *  Created on: 16 ����. 2018 �.
 *      Author: Maksim Fedarenka
 */

#include "ValueWatcher.h"

namespace util {

ValueWatcher::ValueWatcher(EepromLogger *logger, uint8_t logInterval,
        LogType logType) {
    this->logger = logger;
    this->logInterval = logInterval;
    this->logType = logType;
}

uint8_t ValueWatcher::getLogInterval() const {
    return logInterval;
}

void ValueWatcher::setLogInterval(uint8_t logInterval) {
    this->logInterval = logInterval;
}

void ValueWatcher::log(int16_t currentValue) {
    if (currentValue < logger->getMin()) {
        logger->writeMin(currentValue);
        localMinimum = true;
    } else {
        localMinimum = false;
    }

    if (currentValue > logger->getMax()) {
        logger->writeMax(currentValue);
        localMaximum = true;
    } else {
        localMaximum = false;
    }

    if ((localMinimum && logType == VALUE_RISING)
            || (localMaximum && logType == VALUE_FALLING)) {
        logger->clearChangesLog();
        delete timer;
        timer = new Timer();
        timer->setSecondsInterval(logInterval);
    }

    if (timer != NULL) {
        if (timer->isTimeOut()) {
            switch (logType) {
            case VALUE_FALLING:
                logger->writeNextValue(currentValue);
                break;
            case VALUE_RISING:
                logger->writeNextValue(currentValue);
                break;
            default:
                break;
            }
        }
    }

    prevVal = currentValue;
}

} /* namespace util */
