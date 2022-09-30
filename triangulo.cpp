#include <iostream>
using namespace std;

int main()
{
	double	base, altura;

	cout << "Base del triangulo: ";
	cin >> base;

	cout << "Altura del triangulo: ";
	cin >> altura;

	cout << "La area del triangulo es " << base * altura / 2 << endl;

	return 0;
}