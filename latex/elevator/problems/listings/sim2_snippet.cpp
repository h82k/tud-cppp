... iter = containedPeople. ...;		// create iterator for containedPeople
// iterate through all elements
while (iter != ...) {
	PersonPtr person = ... iter; 		// get person smart pointer at current position
	// check whether person has reached it's destination Floor
	if (...) {
		// erase person pointer from containedPeople
		// no need for ++iter since iter will already point to next item
		... = containedPeople.erase(iter);
		// remember arrived person
		...
	}
	else {
		++iter; // check next person
	}
}
