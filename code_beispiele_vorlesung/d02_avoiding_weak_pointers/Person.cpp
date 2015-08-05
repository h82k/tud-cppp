/*
 * Person.cpp
 *
 *  Created on: 26.08.2014
 *      Author: rkluge
 */

#include "Person.h"

Person::Person(const std::string &name, double weight) :
		name(name), weight(weight) {
}

const std::string &Person::getName() const {
	return this->name;
}

void Person::setWeight(double weight) {
	this->weight = weight;
}

double Person::getWeight() const {
	return this->weight;
}

std::vector<Person> &Person::getFriends() {
	return this->friends;
}

void Person::makeFriends(Person &person1, Person &person2) {
	person1.friends.push_back(person2);
	person2.friends.push_back(person1);
}

