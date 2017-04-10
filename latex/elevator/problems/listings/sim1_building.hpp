class Building {
public:
    Building(int numberOfFloors);   // create a Building with given number of floors
    int getNumOfFloors();           // get number of floors
    Floor& getFloor(int floor);     // get a certain floor
    Elevator& getElevator();        // get the elevator
private:
    std::vector<Floor> floors;      // floors of this building
    Elevator elevator;              // the elevator
};
