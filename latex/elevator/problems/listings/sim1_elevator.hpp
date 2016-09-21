class Elevator {
public:
    Elevator();                                 // create an elevator at floor 0, no people inside and 0 energy consumed
    int getFloor();                             // get number of floor the elevator is currently at
    double getEnergyConsumed();                 // get consumed energy
    void moveToFloor(int floor);                // move the elevator to given floor (consumes energy)
    int getNumPeople();                         // get number of people in Elevator
    Person getPerson(int i);                    // get i-th person in Elevator
    void addPeople(std::vector<Person> people); // add people to Elevator
    std::vector<Person> removeArrivedPeople();  // remove people which arrived
private:
    int currentFloor;                           // current floor number
    std::vector<Person> containedPeople;        // people currently in elevator
    double energyConsumed;                      // energy consumed
};
