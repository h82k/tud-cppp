// STILL UNDER CONSTRUCTION - MAY NOT COMPILE!

// Avoid multiple includes of this header filebuf
// Alternative 1:
#pragma once
// Alternative 2 (see also last line):
#ifndef LIVING_CHEATSHEET_HPP
#define LIVING_CHEATSHEET_HPP

#include <string> // Import from global include path (e.g., STL)
#include <vector>

// AVOID using 'using' in the header! May lead to name clashes if not used very carefully.
// using std::endl;
// using namespace std;

class MyPrivateClass; // Forward declaration

template<class T> // Alternative (almost equiv.): typename
class LivingCheatSheet
{
// Convention: public -> protected -> private, avoid mixing
public:

    LivingCheatSheet(const int x) : x(x) // Member x needs to be initialized here because 
    {
    }
    
    ~LivingCheatSheet() {}

    std::vector<std::string> &getNames()
    {
       return this->names; // this-> is optional, equivalent to this. in Java
    }
    
    // Const overload
    std::vector<std::string> &getNames() const
    {
        return names;
    }
    
    void doItInTheSubclasses() = 0; // pure virtual function
    
    
    
protected:
    
private:
    MyPrivateClass *x;
    const int y; // Unmodifiable member
    std::vector<std::string> names;
    
friend std::ostream &stream operator<<(std::ostream &stream, const LivingCheatSheet &lcs);
}; // <- mind semicolon

std::ostream &stream operator<<(std::ostream &stream, const LivingCheatSheet &lcs)
{
    stream << lcs.y << std::endl;
    return stream;
}

#endif LIVING_CHEATSHEET_HPP
