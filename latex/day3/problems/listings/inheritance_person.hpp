class Person {
public:
    Person(const std::string &name);        // initialize the name of the person
    ~Person();                              // destructor
    std::string getInfo() const;            // get the name of the person
protected:
    std::string name;                       // the name of the person
};
