#include <iostream>
using namespace std;

int main()
{
	double radio;
	double pi = 3.14159;

	cout << "Introduzca el radio del circulo: ";
	cin >> radio;
	cout << "El area de un circulo de radio " << radio << " es igual a " << (pi * radio * radio) << endl;

	return (0);
}