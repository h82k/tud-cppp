#ifndef PERSON_H_
#define PERSON_H_

#include <vector>
#include <string>

class Person {
public:
	Person(const std::string &name, double weight);

	static void makeFriends(Person &p1, Person &p2);

	// N.B. It would be better to make this method const, but then the example fails :-)
	std::vector<Person> &getFriends();

	const std::string &getName() const;

	double getWeight() const;
	void setWeight(double weight);
private:
	std::string name;
	double weight;
	std::vector<Person> friends;
};

#endif /* PERSON_H_ */
