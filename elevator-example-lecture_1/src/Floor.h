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
	~Floor();
	Floor(const Floor& floor);

	inline int getNumber() const {
		return number;
	}

private:
	int number;
};

#endif /* FLOOR_H_ */
