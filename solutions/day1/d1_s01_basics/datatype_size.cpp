#include <iostream>
#include <limits>

template<typename T> void print_info(T a) {
    std::cout   << sizeof(a) << "\t"
                << std::numeric_limits<T>::min() << "\t"
                << std::numeric_limits<T>::max() << "\t"
                << std::endl;
}

int main() {
    int a;
    unsigned int b;
    double c;
    unsigned int d;
    bool e;
    
    print_info(a);
    print_info(b);
    print_info(c);
    print_info(d);
    print_info(e);
}

