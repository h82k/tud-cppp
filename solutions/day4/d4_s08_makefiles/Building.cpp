#include "Building.hpp"
#include <string>

Building::Building(unsigned int numFloors):
	numFloors(numFloors)
{}

const std::string Building::toString() const{
	std::stringstream output;
	output << "A building with " << this->numFloors << " floors \n";
	return output.str();
}
