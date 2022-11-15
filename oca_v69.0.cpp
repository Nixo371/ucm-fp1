#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef struct {
	int	casilla;
	int	tiradas;
}	jugador;

const	bool	MODO_DEBUG = false;

const int NUM_JUGADORES = 4;

int	*crear_tablero();
void imprimir_tablero(int	*tablero, jugador *jugadores);
int	valor_casilla(char	*texto);

int	efecto_posicion(int casilla, int *tablero);
int	siguiente(int casilla, int *tablero, int i);
int	efecto_tiradas(int casilla, int *tablero);

bool	es_meta(jugador *j);
int	tirar_dado();

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
*/

int main()
{
	jugador jugadores[NUM_JUGADORES];
	int	turno;
	int dado;
	int	*tablero;

	srand(time(NULL));

	for(int i = 0; i < NUM_JUGADORES; i++)
	{
		jugadores[i].casilla = 1;
		jugadores[i].tiradas = 0;
	}
	turno = (rand() % NUM_JUGADORES); // Elegir aleatoriamente el primer jugador
	tablero = crear_tablero();
	imprimir_tablero(tablero, jugadores);
	cout << "***Empieza el jugador " << turno + 1 << "***" << endl;
	jugadores[turno].tiradas = 1;
	while(!es_meta(jugadores))
	{
		while(jugadores[turno].tiradas > 0 && !es_meta(jugadores))
		{
			cout << "Partimos de la casilla " << jugadores[turno].casilla << endl; 
			dado = tirar_dado();
			jugadores[turno].casilla += dado;
			jugadores[turno].tiradas--;
			jugadores[turno].casilla = efecto_posicion(jugadores[turno].casilla, tablero);
			jugadores[turno].tiradas += efecto_tiradas(jugadores[turno].casilla, tablero);
			imprimir_tablero(tablero, jugadores);
		}
		if(jugadores[turno].casilla >= 63)
		{
			cout << endl << endl << "***Ha ganado el jugador " << turno + 1 << "!***" << endl;
			return(0);
		}
		turno = (turno + 1) % NUM_JUGADORES; // Rotar entre jugadores
		jugadores[turno].tiradas++;
		while(jugadores[turno].tiradas <= 0) // Si el jugador no tiene tiradas (por perder turnos)
		{
			cout << "Al jugador " << turno + 1 << " se le salta el turno" << endl;
			turno = (turno + 1) % NUM_JUGADORES;
			jugadores[turno].tiradas++;
		}
		cout << endl << "Turno del jugador " << turno + 1 << endl;
	}
	return(0);
}

int	*crear_tablero()
{
	ifstream	infile;
	int			casilla;
	char		texto[10];
	int			*tablero;

	infile.open("tablero_69.txt");
	if(!infile)
	{
		cerr << "No se pudo abrir el archivo" << endl;
		exit(EXIT_FAILURE);
	}

	tablero = new int[63];
	for(int i = 0; i < 63; i++)
		tablero[i] = 0;
	tablero[62] = 1;

	do
	{
		infile >> casilla;
		if (!casilla)
			return(tablero);
		infile.ignore(1); // ignorar el espacio
		infile.getline(texto, 10);

		tablero[casilla - 1] = valor_casilla(texto);
	}
	while (casilla);

	return(tablero);
}

int	valor_casilla(char	*texto)
{
	switch(texto[2])
	{
		case 'A':
			return(1); // OCA
		case 'E':
			return(2); // PUENTE
		case 'S':
			return(3); // POSADA
		case 'Z':
			return(4); // POZO
		case 'B':
			return(5); // LABERINTO
		case 'R':
			return(6); // CARCEL
		case 'D':
			return(7); // DADOS
		case 'L':
			return(8); // CALAVERA
	}
	return(0);
}

void imprimir_tablero(int	*tablero, jugador *jugadores)
{
	int c = 1;
	cout << "|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|" << endl;
	
	for(int i = 0; i < 3; i++)
	{
			cout << "|";

		for(int i = c; i < c + 21; i++)
		{
			if(i < 10)
				cout << " 0" << i << " |";
			else
				cout << " " << i << " |";
		}
		cout << endl;

		cout << "|";
		for(int i = c; i < c + 21; i++)
		{
			switch(tablero[i - 1])
			{
				case 0:
					cout << "    ";
					break;
				case 1:
					cout << " OCA";
					break;
				case 2:
					cout << "PNTE";
					break;
				case 3:
					cout << "PSDA";
					break;
				case 4:
					cout << "POZO";
					break;
				case 5:
					cout << "LBRN";
					break;
				case 6:
					cout << "CRCL";
					break;
				case 7:
					cout << "DADO";
					break;
				case 8:
					cout << "MUER";
					break;
			}
			cout << "|";
		}
		cout << endl;

		cout << "|";
		for(int i = c; i < c + 21; i++)
		{
			if(jugadores[0].casilla == i)
				cout << "1";
			else
				cout << " ";
			
			if(jugadores[1].casilla == i)
				cout << "2";
			else
				cout << " ";

			if(jugadores[2].casilla == i && NUM_JUGADORES >= 3)
				cout << "3";
			else
				cout << " ";

			if(jugadores[3].casilla == i && NUM_JUGADORES == 4)
				cout << "4";
			else
				cout << " ";
			cout << "|";
		}
		cout << endl;
		cout << "|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|====|" << endl;
		c += 21;
	}
	
}

bool	es_meta(jugador *j)
{
	for(int	i = 0; i < NUM_JUGADORES; i++)
	{
		if(j[i].casilla >= 63)
			return(true);
	}
	return(false);
}

int	tirar_dado()
{
	int	dado;

	if(MODO_DEBUG)
	{
		cout << "Introduzca el valor del dado: ";
		cin >> dado;
	}
	else
		dado = (rand() % 6) + 1;
	cout << "Valor del dado: " << dado << endl;
	return(dado);
}

int	efecto_posicion(int casilla, int *tablero)
{
	int	i;

	if(casilla >= 63 || casilla < 0)
		return(casilla);

	i = tablero[casilla - 1];

	switch(i)
	{
		case 0: // NADA
			return(casilla);
		case 1: // OCA
			cout << "De oca a oca y tiro porque me toca!" << endl;
			return(siguiente(casilla, tablero, i));
		case 2: // PUENTE
			cout << "De puente a puente y tiro porque me lleva la corriente" << endl;
			return(siguiente(casilla, tablero, i));
		case 3: // POSADA
			cout << "Has caido en la posada" << endl;
			return(casilla);
		case 4: // POZO
			cout << "Has caido en el pozo" << endl;
			return(casilla);
		case 5: // LABERINTO
			cout << "Has caido en el laberinto, retrocedes 12 casillas" << endl;
			return(casilla - 12);
		case 6: // CARCEL
			cout << "Has caido en la carcel" << endl;
			return(casilla);
		case 7: // DADOS
			cout << "De dado a dado, y tiro porque me ha tocado" << endl;
			return(siguiente(casilla, tablero, i));
		case 8: // MUERTE
			cout << "Has caido en la muerte, vuelves al principio" << endl;
			return(1);
	}
	return(casilla);
}

int	siguiente(int casilla, int *tablero, int i)
{
	casilla++;
	while(tablero[casilla - 1] != i)
	{
		casilla++;
		if(casilla >= 63)
			casilla = 0;
	}
	return(casilla);
}

int	efecto_tiradas(int casilla, int *tablero)
{
	int	i;

	if(casilla >= 63 || casilla < 0)
		return(0);
	
	i = tablero[casilla - 1];

	switch(i)
	{
		case 0: // NADA
			return(0);
		case 1: // OCA
			cout << "+1 tirada" << endl;
			return(1);
		case 2: // PUENTE
			cout << "+1 tirada" << endl;
			return(1);
		case 3: // POSADA
			cout << "-1 turno" << endl;
			return(-1);
		case 4: // POZO
			cout << "-3 turnos" << endl;
			return(-3);
		case 5: // LABERINTO
			return(0);
		case 6: // CARCEL
			cout << "-2 turnos" << endl;
			return(-2);
		case 7: // DADOS
			cout << "+1 tirada" << endl;
			return(1);
		case 8: // MUERTE
			return(0);
	}
	return(0);
}