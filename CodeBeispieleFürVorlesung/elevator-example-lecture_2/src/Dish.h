/*
 * Dish.h
 *
 *  Created on: 01.08.2013
 *      Author: anjorin
 */

#ifndef DISH_H_
#define DISH_H_

#include <string>

using namespace std;

class Dish {
public:
	Dish(const string& name);
	~Dish();

	inline const string& getName() const {
		return name;
	}

	inline double getWeight() const {
		return 1.5;
	}
private:
	const string name;

};

#endif /* DISH_H_ */
