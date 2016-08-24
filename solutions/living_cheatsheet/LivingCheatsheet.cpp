#include "LivingCheatsheet.hpp" // Should always be the first #include


// Only used inside the header
class MyPrivateClass{
    
};

// int main()
int main(int argc, char** argv)
{
    LivingCheatsheet lc1;
    LivingCheatsheet &lc1Ref = lc1;
    LivingCheatsheet &lc1ConstRef = lc1;
    
    LivingCheatsheet *lc2 = new LivingCheatsheet();
    delete lc2;
    
    // return 1; // May be omitted. 0 = success, otherwise: application-specific error code
}