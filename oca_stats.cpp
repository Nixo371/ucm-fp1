#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int oca();
int tirar();
int salto_oca(int pos);

/*
Codigos:
0 - Nada
1 - Oca
2 - Puente
3 - Posada
4 - Pozo
5 - Laberinto
6 - Carcel
7 - Dados
8 - Calavera
69 - Ultima oca
*/

int main()
{
	int cuenta;
	long int turnos = 0;

	cout << "Cuantas veces quieres simular un juego? ";
	cin >> cuenta;
	for (int i = 0; i <= cuenta; i++)
	{
		turnos += oca();
		if (cuenta % i == 0)
			cout << cuenta / i << "\% completado" << endl;
	}
	cout << "Has simulado " << cuenta << " juegos, en los cuales se han jugado " << turnos << " turnos" << endl;
	cout << "La media son " << turnos / cuenta << " turnos por juego" << endl;

	return (0);
}

int tirar()
{
	int tirada;

	tirada = rand() % 6 + 1;
	return (tirada);
}

int salto_oca(int pos)
{
	int oca[14] = {5, 9, 14, 18, 23, 27, 32, 36, 41, 45, 50, 54, 59, 0};
	for (int i = 0; i < 12; i++)
	{
		if (pos == oca[i])
			return (oca[i + 1]);
	}
	perror("Salto oca");
	return (0);
}

int oca()
{
	int tablero[63] = {0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0, 1, 3, 0, 0, 0, 1, 0, 0, 7, 1, 0, 0, 0, 4, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 5, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 7, 1, 0, 6, 0, 8, 69, 0, 0, 0, 0, };
	int pos_jugador = 1;
	int tirada;
	int turno = 1;

	srand(time(NULL)); //"Aleatorio"
	while (pos_jugador != 63)
	{
		//sleep(2);
		if (pos_jugador > 63)
			pos_jugador = 63 - (pos_jugador - 63); // El "rebote" que ocurre al llegar al final con mas casillas de movimiento
		tirada = tirar();
		pos_jugador += tirada;
		if (pos_jugador > 63)
			pos_jugador = 63 - (pos_jugador - 63); // El "rebote" que ocurre al llegar al final con mas casillas de movimiento
		
		while (tablero[pos_jugador - 1] == 1) //Has caido en una oca que no es la ultima
		{
			pos_jugador = salto_oca(pos_jugador);
			tirada = tirar();
			pos_jugador += tirada;
		}
		if (tablero[pos_jugador - 1] == 2) //Has caido en un puente
		{
			pos_jugador = 19;
		}
		if (tablero[pos_jugador - 1] == 3) //Has caido en la posada (o te ha llevado un puente)
		{
			turno++;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 4) //Has caido en el pozo
		{
			turno += 2;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 5) //Has caido en el laberinto
		{
			pos_jugador = 30;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 6) //Has caido en la carcel
		{
			turno += 2;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 7) //Has caido en los dados
		{
			pos_jugador += pos_jugador + tirada;
			continue;
		}
		if (tablero[pos_jugador - 1] == 8) //Has caido en la calavera
		{
			pos_jugador = 1;
			continue;
		}
		turno++;
	}
	return (turno);
}