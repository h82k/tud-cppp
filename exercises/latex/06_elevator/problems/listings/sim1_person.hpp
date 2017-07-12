class Person {
public:
    Person(int destinationFloor);       // create a person with given destination
    Person(const Person& other);        // copy constructor
    ~Person();                          // destructor
    int getDestinationFloor() const;    // get the destination floor of this person
private:
    int destinationFloor;               // destination floor of this person
};
