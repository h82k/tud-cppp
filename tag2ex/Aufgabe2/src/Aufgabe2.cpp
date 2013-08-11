//============================================================================
// Name        : Aufgabe2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

// Teil b)
void printArray(const int *arr, int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;
}

// Teil c)
void printArrayPointer(const int *arr, int size) {
	for (const int *p = arr; p != arr + size; p++)
		cout << *p << endl;
}

// Teil d)
void printArray(const int *begin, const int *end) {
	for (const int *p = begin; p != end; p++)
		cout << *p << endl;
}

int* readNumbers(int *size) {
	int n;
	cout << "Geben Sie die Größe ein: ";
	cin >> n;
	
	cout << "Geben Sie " << n << " Zahlen ein: " << endl;
	int *arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	
	*size = n;
	return arr;
}

int main() {
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	// a)
	//	for (int i = 0; i < 10; i++)
	//		cout << arr[i] << endl;
	
	// b)
	printArray(arr, 10);
	
	// c)
	// printArrayPointer(arr, 10);
	
	// d)
	// printArray(arr, arr + 10);
	
	// e)
	// printArray(arr + 3, arr + 7); // elements 4, 5, 6, 7
	
	// f)
	int size; // variable to store array size
	int *pArr = readNumbers(&size); // read some numbers
	
	printArray(pArr, pArr + size); // print the numbers
	
	delete[] pArr; // delete array
	pArr = NULL; // avoid dangling pointer
	
	return 0;
}
