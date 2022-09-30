#include <iostream>

using namespace std;

int main()
{
	int mayor;
	int num;
	int i;

	i = 0;
	while (++i <= 10)
	{
		cout << "Introduzca el numero #" << i << ": ";
		cin >> num;
		if (i == 1)
			mayor = num;
		if (num > mayor)
			mayor = num;
	}
	cout << "El mayor de los 10 numeros es: " << mayor << endl;
	return (0);
}