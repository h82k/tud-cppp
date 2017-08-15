class Building {
public:
    // ...

    /** Gets a certain, const floor */
    const Floor& getFloor(int floor) const;

private:
    /** Returns the floor with the given number. 
     *  This non-const variant of the getter is for 'private' purposes only. 
     */
    Floor& getFloor(int floor);

    // ...
};
