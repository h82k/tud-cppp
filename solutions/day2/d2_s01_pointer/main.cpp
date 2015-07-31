#include <iostream>
using namespace std;

/**
*****************************************
Aufgabe 1 Teil b) 
*****************************************
*&intVal	Wert von intVal
*&pIntVal	Wert von pIntVal (Adresse von intVal)
&*pIntVal	Wert von pIntVal (Adresse von intVal)
**&pIntVal	Wert von intVal
*&*&intVal	Wert von intVal
&*&pIntVal	Adresse von pIntVal (Adresse von intVal)
*&*pIntVal	Wert von intVal
*****************************************
Aufgabe 1 Teil c)
*****************************************
*intVal		intVal ist kein Zeiger, kann also auch nicht dereferenziert werden
**pIntVal	*pIntVal ist ein int, also kein Zeiger und kann somit auch nicht weiter dereferenziert werden
**&*pIntVal	*pIntVal ist ein int, &*pIntVal ist ein Zeiger auf einen int, *&*pIntVal ist wieder ein int, 
			also kann er nicht weiter derefernziert werden
&*intVal	intVal ist ein int, kann also nicht dereferenziert werden.
&42			42 ist ein Literal vom Typ int und keine Variable. Nur Variablen haben Adressen im Speicher.
 */

void swapPointer(int *i1, int *i2) {
	int tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

void swapReference(int& i1, int& i2) {
	int tmp = i1;
	i1 = i2;
	i2 = tmp;
}

void foo(int& i) {
	int i2 = i;
	int& i3 = i;
	cout << "i = " << i << endl;
	cout << "i2 = " << i2 << endl;
	cout << "i3 = " << i3 << endl;
	cout << "&i = " << &i << endl;
	cout << "&i2 = " << &i2 << endl;
	cout << "&i3 = " << &i3 << endl;
}

int main() {
	// Teil d)
	int i1 = 3, i2 = 5;
	cout << i1 << " " << i2 << endl;
	swapPointer(&i1, &i2);
	cout << i1 << " " << i2 << endl;
	swapReference(i1, i2);
	cout << i1 << " " << i2 << endl;
	// Teil f)
	int var = 42;
	cout << "&var = " << &var << endl;
	foo(var);
}

