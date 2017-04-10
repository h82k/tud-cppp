void letPeopleIn();                                 // let people on current floor into elevator
void moveElevatorToFloor(int i);                    // move the elevator to a given floor
void addWaitingPerson(int floor, Person p); // add a person to a given floor
std::vector<Person> removeArrivedPeople();  // remove people which arrived at their destination from the elevator on the current floor
