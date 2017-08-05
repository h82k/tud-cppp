#include <iostream>

// Task 6.2
void printArray(const int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << std::endl;
	}
}

// Task 6.3
void printArrayPointer(const int *arr, int size) {
	for (const int *p = arr; p != arr + size; ++p) {
		std::cout << *p << std::endl;
	}
}

// Task 6.4
void printArray(const int *begin, const int *end) {
	for (const int *p = begin; p != end; ++p) {
		std::cout << *p << std::endl;
	}
}

int* readNumbers(int *size) {
	int n;
	std::cout << "Geben Sie die Groesse ein: ";
	std::cin >> n;
	
	std::cout << "Geben Sie " << n << " Zahlen ein: " << std::endl;
	int *arr = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}
	*size = n;
	return arr;
}

int main() {
	// Task 6.1
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i = 0; i < 10; ++i) {
		std::cout << arr[i] << std::endl;
	}
	
	// Task 6.2
	printArray(arr, 10);
	
	// Task 6.3
	printArrayPointer(arr, 10);
	
	// Task 6.4
	printArray(arr, arr + 10);
	
	// Task 6.5
	printArray(arr + 3, arr + 7); // elements 4, 5, 6, 7
	
	// Task 6.6
	int size;	// variable to store array size
	int *pArr = readNumbers(&size);		// read some numbers
	
	printArray(pArr, pArr + size);		// print the numbers
	
	delete[] pArr;	// delete array
	pArr = NULL;	// avoid dangling pointer
}
