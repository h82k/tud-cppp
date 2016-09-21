#include "Array.h"
#include <iostream>
#include <string>

template<typename T>
void printFirst(const Array<T> &array) {
    std::cout << array[0] << std::endl;
}

int main() {
    Array<std::string> stringArray(10);
    stringArray[0] = "Hello World";
    printFirst(stringArray);
}

