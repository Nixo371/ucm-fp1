#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

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
		cout << endl << endl << "Estas en la casilla " << pos_jugador << "..." << endl;
		tirada = tirar();
		cout << "Tiras el dado...";
		cout << " y sacas un " << tirada << "!" << endl;
		pos_jugador += tirada;
		if (pos_jugador > 63)
			pos_jugador = 63 - (pos_jugador - 63); // El "rebote" que ocurre al llegar al final con mas casillas de movimiento
		
		while (tablero[pos_jugador - 1] == 1) //Has caido en una oca que no es la ultima
		{
			cout << "De oca a oca..." << endl;
			pos_jugador = salto_oca(pos_jugador);
			cout << "Has saltado a la casilla " << pos_jugador << endl;
			cout << "...y tiro porque me toca!" << endl;
			tirada = tirar();
			cout << "Tiras el dado...";
			//sleep(1);
			cout << " y sacas un " << tirada << "!" << endl;
			pos_jugador += tirada;
		}
		if (tablero[pos_jugador - 1] == 2) //Has caido en un puente
		{
			cout << "Has caido en un puente..." << endl;
			cout << "Te vas a la Posada(19)" << endl;
			pos_jugador = 19;
		}
		if (tablero[pos_jugador - 1] == 3) //Has caido en la posada (o te ha llevado un puente)
		{
			cout << "Has caido en la posada..." << endl;
			cout << "Te quedas a dormir un turno" << endl;
			cout << "z.";
			//sleep(1);
			cout << "z..";
			//sleep(1);
			cout << "z..." << endl;
			//sleep(1);
			turno++;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 4) //Has caido en el pozo
		{
			/*
				Las reglas del juego indican que hay que esperar a otro jugador
				para que te rescate. Este juego esta programado para un jugador por ahora,
				por lo que su funcionamiento sera perder dos turnos por ahora
			*/
			cout << "Te has caido en un pozo..." << endl;
			turno += 2;
			cout << "Has tardado 2 turnos en salir..." << endl;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 5) //Has caido en el laberinto
		{
			cout << "Te encuentras perdido en un laberinto..." << endl;
			cout << "Al salir, ves que has retrocedido 12 casillas, hasta la 30" << endl;
			pos_jugador = 30;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 6) //Has caido en la carcel
		{
			cout << "Te despiertas tras unos barrotes en la carcel" << endl;
			cout << "2 Turnos sin jugar..." << endl;
			turno += 2;
			continue; //No comprobar el resto de tiradas posibles, ya que no es posible
		}
		if (tablero[pos_jugador - 1] == 7) //Has caido en los dados
		{
			cout << "Te encuentras unos dados magicos..." << endl;
			cout << "Al tirarlos te sale el numero " << pos_jugador + tirada << endl;
			cout << "Te mueves " << pos_jugador + tirada << " casillas" << endl;
			pos_jugador += pos_jugador + tirada;
			continue;
		}
		if (tablero[pos_jugador - 1] == 8) //Has caido en la calavera
		{
			cout << "Teniendo el final a vista te encuentras una calavera en el camino" << endl;
			cout << "Mientras te agachas a verlo de cerca, de repente todo se hace oscuro" << endl;
			cout << "Te despiertas desde el punto de partida, la casilla 1" << endl;
			pos_jugador = 1;
			continue;
		}
		turno++;
	}
	cout << "Has ganado!" << endl;
	cout << "Has tardado " << turno << " turnos para llegar a la meta." << endl;
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