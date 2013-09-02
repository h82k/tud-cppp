#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "Person.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T = Person>
class Elevator {
public:
	Elevator(){
		cout << "Elevator()" << endl;
	}
	~Elevator(){
		cout << "~Elevator()" << endl;
	}

	void placeInElevator(const T* object){
		cout << "Adding " << object->getName()
			 << " with weight: "
			 << object->getWeight() << " to elevator.";
		cout << endl;

		transportedObjects.push_back(object);
	}

private:
	vector<const T*> transportedObjects;
};

#endif /* ELEVATOR_H_ */
