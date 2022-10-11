#include <iostream>

using namespace std;

int suma_digitos(int num);

int main()
{
	int	num;
	int magico;

	cout << "Introduzca un numero: ";
	cin >> num;

	magico = suma_digitos(num);
	while (magico >= 10)
		magico = suma_digitos(magico);
	cout << "El digito magico es: " << magico << endl;
}

int suma_digitos(int num)
{
	if (num < 10)
		return (num);
	//funcion recursiva que separa numeros y los suma hasta llegar a la solucion
	return (suma_digitos(num % 10) + suma_digitos(num / 10));
}
