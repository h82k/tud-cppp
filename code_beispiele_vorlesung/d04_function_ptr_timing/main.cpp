#include <ctime>

class Timer {
public:
	double measureDuration(unsigned long iterations,
			void (*fp)(unsigned long)) {
		tic();
		fp(iterations);
		toc();
		return getElapsedTime();
	}

	void tic() {
		begin = std::clock();
	}
	void toc() {
		end = std::clock();
	}
	double getElapsedTime() {
		return double(end - begin) / CLOCKS_PER_SEC;
	}
private:
	clock_t begin;
	clock_t end;
};

void mySophisticatedAlgorithm(unsigned long iterations) {
	long k = 0;
	// Running time depends quadratically of the number of iterations
	for (unsigned long i = 0; i < iterations; ++i) {
		for (unsigned long j = i; j < iterations; ++j) {
			k += j;
		}
	}
}

#include <iostream>
#include <vector>

typedef unsigned long iter_t;
int main() {
	Timer t;
	std::vector<iter_t> iterationCounts { 100, 1000, 10000, (iter_t) 1e5,
	//(iter_t) 1e6, (iter_t) 1e7
	};
	for (iter_t&i : iterationCounts) {
		std::cout << "Duration for " << i << " iterations: "
				<< t.measureDuration(i, mySophisticatedAlgorithm) << std::endl;

	}

	std::cout << "Done" << std::endl;
}
