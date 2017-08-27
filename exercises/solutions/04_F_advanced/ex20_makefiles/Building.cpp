#include "Building.hpp"
#include <sstream>

Building::Building(size_t numFloors):
	numFloors(numFloors)
{}

const std::string Building::toString() const{
	std::stringstream output;
	output << "A building with " << numFloors;
	output << " floors" << std::endl;
	return output.str();
}
