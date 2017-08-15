#include <sstream>
// ...
const std::string toString() const{

    std::stringstream output;
    output << "A building with " << this->numFloors << " floors" << std::endl;
    return output.str();
}
