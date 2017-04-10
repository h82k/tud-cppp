#include "functions.hpp"
#include <iostream>
#include <limits>

void print_easy() {
    /**
     * @brief easy version of solution of 1.1
     * prints size in bytes of int, unsigned int, double, unsigned short, bool 
     * to the standard output, as well as their minimum and maximum value.
     *
     * @return void
     */

    int a;
    unsigned int b;
    double c;
    unsigned short d;
    bool e;

    std::cout   << sizeof(a) << "\t"
                << std::numeric_limits<int>::min() << "\t"
                << std::numeric_limits<int>::max() << "\t"
                << std::endl;
    
    std::cout   << sizeof(b) << "\t"
                << std::numeric_limits<unsigned int>::min() << "\t"
                << std::numeric_limits<unsigned int>::max() << "\t"
                << std::endl;
    
    std::cout   << sizeof(c) << "\t"
                << std::numeric_limits<double>::min() << "\t"
                << std::numeric_limits<double>::max() << "\t"
                << std::endl;
    
    std::cout   << sizeof(d) << "\t"
                << std::numeric_limits<unsigned short>::min() << "\t"
                << std::numeric_limits<unsigned short>::max() << "\t"
                << std::endl;
    
    std::cout   << sizeof(e) << "\t"
                << std::numeric_limits<bool>::min() << "\t"
                << std::numeric_limits<bool>::max() << "\t"
                << std::endl;
}

template<typename T> void print_info_advanced(T a) {
    /**
     * @brief advanced version of solution of 1.1
     * helper function for advanced solution
     * will be explained in detail on day 4
     *
     * @return void
     */
    std::cout   << sizeof(a) << "\t"
                << std::numeric_limits<T>::min() << "\t"
                << std::numeric_limits<T>::max() << "\t"
                << std::endl;
}

void print_advanced() {
    /**
     * advances solution using the helper function print_info_advanced
     * prints the same information as print_easy to the standard output
     * 
     * @retun: void
     */
    int a;
    unsigned int b;
    double c;
    unsigned short d;
    bool e;
    
    print_info_advanced(a);
    print_info_advanced(b);
    print_info_advanced(c);
    print_info_advanced(d);
    print_info_advanced(e);
}


int main() {
    print_easy();
	fun::task_e();
}
