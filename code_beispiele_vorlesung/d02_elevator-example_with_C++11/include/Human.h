/*
 * Human.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include <memory>

class Human {
public:
	Human(int destinationFloor);
	
	inline int destinationFloor() const {
		return destinationFloor_;
	}
	
private:
	int destinationFloor_;
};


typedef std::shared_ptr<Human> HumanPtr;
typedef std::shared_ptr<const Human> ConstHumanPtr;

#endif /* HUMAN_H_ */
