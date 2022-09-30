#include <iostream>

using namespace std;

int suma_digitos(int num);

int main()
{
	int	num;

	cout << "Introduzca un numero: ";
	cin >> num;

	cout << "La suma de los digitos del numero " << num << " es: " << suma_digitos(num) << endl;
}

int suma_digitos(int num)
{
	if (num < 10)
		return (num);
	return (suma_digitos(num % 10) + suma_digitos(num / 10));
}
