/*
 * Logger.h
 *
 *  Created on: 14 ����. 2018 �.
 *      Author: ����
 */

#ifndef UTIL_LOGGER_H_
#define UTIL_LOGGER_H_

namespace components {

class Logger {
private:
    unsigned char min;
    unsigned char max;
public:
    Logger();
    virtual ~Logger();
};

} /* namespace components */

#endif /* UTIL_LOGGER_H_ */
