# pragma once

#include <string>
#include <cstddef>

class Building {
public:
	Building(size_t numFloors);
	const std::string toString() const;
private:
	size_t numFloors;
};
