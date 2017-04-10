class Vector3 {
public:
	Vector3();											// initialize vector with zero
	Vector3(double a, double b, double c);		// initialize vector with a, b, c
	Vector3(const Vector3 &other);				// copy constructor: copy a vector
	~Vector3();											// destructor: destroy the vector
private:
	double a, b, c;									// vector components
};
