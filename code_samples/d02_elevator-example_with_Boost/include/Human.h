/*
 * Human.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include <boost/shared_ptr.hpp>

class Human {
public:
	Human(int destinationFloor);
	
	inline int destinationFloor() const {
		return destinationFloor_;
	}
	
private:
	int destinationFloor_;
};


typedef boost::shared_ptr<Human> HumanPtr;
typedef boost::shared_ptr<const Human> ConstHumanPtr;

#endif /* HUMAN_H_ */
