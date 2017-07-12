#pragma once 
#include <string>

class Building {
public:
    Building(unsigned int numFloors);
    const std::string toString() const;
private:
    unsigned int numFloors;
};
