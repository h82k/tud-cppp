#include <string>

class Student     {public: std::string name; };
class Mitarbeiter {public: std::string name; };

class HiWi: public Student, public Mitarbeiter {};

int main() {

	HiWi* h = new HiWi();
	h->Student::name = "Christian";
	h->Mitarbeiter::name = "Mark";
	// h->name; /* Error: request for name is ambiguous */

}
