/*
 * ConsoleLogger.h
 *
 *  Created on: 02.08.2013
 *      Author: anjorin
 */

#ifndef CONSOLELOGGER_H_
#define CONSOLELOGGER_H_

#include <string>
#include <iostream>

class ConsoleLogger {
public:
	ConsoleLogger();
	~ConsoleLogger();

	inline void operator()(int i) const {
		std::cout << "user:~ /$ " << i << std::endl;
	}

	inline void print(const std::string& message) const {
			std::cout << "user:~ /$ " << message << std::endl;
	}
};

#endif /* CONSOLELOGGER_H_ */
