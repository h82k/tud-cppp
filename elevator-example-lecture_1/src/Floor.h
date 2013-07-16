/*
 * Floor.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef FLOOR_H_
#define FLOOR_H_

class Floor {
public:
	Floor(int number);
	Floor(const Floor& floor);
	~Floor();

	inline int getNumber() const {
		return number;
	}

	inline void setNumber(int n) {
		number = n;
	}

private:
	int number;
};

#endif /* FLOOR_H_ */
