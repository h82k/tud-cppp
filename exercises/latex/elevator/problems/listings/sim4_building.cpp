#include "Building.h"
#include <sstream>

Building::Building(unsigned int numFloors):
    numFloors(numFloors) {}

const std::string Building::toString() const{
    std::stringstream output;
    output << "A building with " << numFloors;
    output << " floors" << std::endl;
    return output.str();
}
