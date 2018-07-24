// 1. Catch by value
try {
	throw C();		// create new object of class C and throw it
} catch(C c) {		// catch c by value => a copy of c is created when catching
	...
}

// 2. Catch by reference
try {
	throw C();				// create new object of class C and throw it
} catch(const C &c) {	// catch c by reference, no copy is created
	...
}
