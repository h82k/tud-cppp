/*
 * PasswordSecurity.h
 *
 *  Created on: 02.08.2013
 *      Author: anjorin
 */

#ifndef PASSWORDSECURITY_H_
#define PASSWORDSECURITY_H_

#include <string>

class PasswordSecurity{

public:
	inline bool checkPassword(const std::string& password){
		return false;
	}
};


#endif /* PASSWORDSECURITY_H_ */
