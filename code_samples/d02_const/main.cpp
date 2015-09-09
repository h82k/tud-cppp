class C {
	int inspect() const;
};

int main(int argc, char** argv) {

	const int i = 3;		// equiv. to const int j = 3;

	int const * iP = &i;	// pointer to const
	int const &iR = i;		// reference to const

	int j = 3;
	int * const iP2 = &j; 	// const pointer
	//int & const iR2 = j;	// const reference = nonsense

	// 1st const : the strings in the array are constant
	// 2nd const : the array of pointers to the strings cannot be modified
	// 3rd const : the pointer argcConst cannot be changed
	char const * const * const argvConst = argv;
	// char const ** argvConst2 = argv; 	// not allowed, would circument const correctness
}
