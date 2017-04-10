#include<utility>
typedef std::pair<int, int> intpair;

void hanoi(..., CallbackBase<intpair> *callback) {
	// ...
	callback->call(intpair(a, c));
	// ...
}

int main() {
	// ...
	CallbackBase<intpair> *function =
	    new FunctionCallback<intpair>(printMovePair);
	hanoi(3,1,2,3, function);
	// ...
}

