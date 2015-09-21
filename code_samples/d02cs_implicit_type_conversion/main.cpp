#include <string>

class Student {
public:
	// Try out:
	//		Student(std::string &name)
	// This should result in a compiler error because the code in main
	// instantiates an anonymous object

	// Try out:
	//		explicit Student(const std::string &name)
	// Now, the function 'useStudent' cannot be called with an std::string
	// because there exists no implicit type conversion from std::string
	// to Student.
	Student(const std::string &name) :
			name(name) {
	}
private:
	std::string name;
};

void useStudent(const Student &student) {
}

int main() {
	Student mike("Mike");

	useStudent(mike);
	useStudent(std::string("Sarah"));
}
