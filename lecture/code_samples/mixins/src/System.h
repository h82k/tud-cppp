/*
 * System.h
 *
 *  Created on: 02.08.2013
 *      Author: anjorin
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

template<class Logger,
		 class Security,
		 class OperatingSystem,
		 class Platform>
class System : public Logger,
			   public Security,
			   public OperatingSystem,
			   public Platform {};


#endif /* SYSTEM_H_ */
