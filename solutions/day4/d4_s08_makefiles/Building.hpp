#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <string>
#include <sstream>

class Building {
public:
	Building(unsigned int numFloors);
	const std::string toString() const;
private:
	unsigned int numFloors;
};

#endif
