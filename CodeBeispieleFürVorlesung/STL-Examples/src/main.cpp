/*
 * main.cpp
 *
 *  Created on: 04.08.2013
 *      Author: anjorin
 */

#include <iostream>
#include <queue>
#include <functional>

using namespace std;

template<class T>
void print_queue(T& queue){
	while(!queue.empty()){
			cout << queue.top() << ",";
			queue.pop();
	}
}

int main(int argc, char **argv) {
	int numbers[] = {3,2,1,5,4};

	priority_queue<int> descending(numbers, numbers + 5);
	print_queue(descending);

	priority_queue<int, vector<int>, greater<int> > ascending(numbers, numbers + 5);
	print_queue(ascending);
}
