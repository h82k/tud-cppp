#include <string>
#include <memory>

class Person {
public:
	Person(const std::string &name) : name(name)  {}
private:
	std::string name;
};

int main() {
	Person *leila = new Person("Leila");
	delete leila;

	std::shared_ptr<Person> mike(new Person("Mike"));

	// std::make_shared handles exceptions appropriately and is (a little) more efficient
	std::shared_ptr<Person> susan = std::make_shared<Person>("Susan");
}


