#include <iostream>
#include <cstdlib>

using namespace std;

const bool	MODO_DEBUG = true;

const int	NUM_CASILLAS = 63;
const int	CASILLA_PUENTE_1 = 6;
const int	CASILLA_PUENTE_2 = 12;
const int	CASILLA_DADOS_1 = 26;
const int	CASILLA_DADOS_2 = 53;
const int	CASILLA_LABERINTO = 42;
const int	CASILLA_MUERTE = 58;
const int	CASILLA_POSADA = 19;
const int	CASILLA_PRISION = 52;
const int	CASILLA_POZO = 31;



bool	esOca(int casilla);
int		siguienteOca(int casilla);

bool	esPuente(int casilla);
int		siguientePuente(int casilla);

bool	esDados(int casilla);
int		siguienteDado(int casilla);

bool	esLaberinto(int casilla);
int		siguienteLaberinto();

bool	esMuerte(int casilla);
int		siguienteMuerte();

bool	esPosada(int casilla);
bool	esPrision(int casilla);
bool	esPozo(int casilla);
bool	esMeta(int casilla);

int		tirarDadoManual();
int		tirarDadoAuto();

int		quienEmpieza();
int		efectoPosicion(int	casilla);
int		efectoTiradas(int	casilla);

int main()
{
	int casillaJugadorConDado = 1;
	int casillaJ1 = 1;
	int	casillaJ2 = 1;
	int dado;
	int	numeroDeTiradas;
	int turno;
	int	jugador;

	srand(time(NULL));

	casillaJ1 = 1;
	casillaJ2 = 1;
	numeroDeTiradas = 1;
	jugador = quienEmpieza();
	cout << "***EMPIEZA EL JUGADOR " << jugador << "***" << endl;
	while(!esMeta(casillaJ1) || !esMeta(casillaJ2))
	{
		while(numeroDeTiradas > 0)
		{
			cout << "Partimos de la casilla: " << casillaJugadorConDado << endl;

			if(MODO_DEBUG)
				dado = tirarDadoManual();
			else
				dado = tirarDadoAuto();
			
			cout << "Valor del dado: " << dado << endl;
			casillaJugadorConDado += dado;
			cout << "Caemos en la casilla " << casillaJugadorConDado << endl;
			casillaJugadorConDado = efectoPosicion(casillaJugadorConDado);
			numeroDeTiradas += efectoTiradas(casillaJugadorConDado);
			numeroDeTiradas--;
		}
		if(casillaJugadorConDado >= 63)
			break;
		numeroDeTiradas = 1 - numeroDeTiradas;
		jugador = (jugador % 2) + 1;
		if (jugador == 1)
		{
			casillaJ2 = casillaJugadorConDado;
			casillaJugadorConDado = casillaJ1;
		}
		else
		{
			casillaJ1 = casillaJugadorConDado;
			casillaJugadorConDado = casillaJ2;
		}
		cout << endl << "Turno Jugador " << jugador << endl;
	}
	cout << "Ha ganado el jugador " << jugador << "!!!" << endl;
	return 0;
}

int	tirarDadoManual()
{
	int	tirada;

	cout << "Introduzca el valor de la tirada: ";
	cin >> tirada;
	
	return (tirada);
}

int tirarDadoAuto()
{
	return ((rand() % 6) + 1);
}

//		OCA		//
bool	esOca(int casilla)
{
	if (casilla % 9 == 0 || (casilla + 4) % 9 == 0)
		return (true);
	return (false);
}
int	siguienteOca(int casilla)
{
	if (esOca(casilla + 4))
		return (casilla + 4);
	return (casilla + 5);
}

//		PUENTES		//
bool	esPuente(int casilla)
{
	if (casilla == 6 || casilla == 12)
		return (true);
	return (false);
}
int	siguientePuente(int casilla)
{
	if (casilla == 6)
		return (12);
	return (6);
}

//		DADOS		//
bool	esDados(int casilla)
{
	if (casilla == 26 || casilla == 53)
		return (true);
	return (false);
}
int	siguienteDado(int casilla)
{
	if (casilla == 26)
		return (53);
	return (26);
}

//		LABERINTO		//
bool	esLaberinto(int casilla)
{
	if (casilla == 42)
		return (true);
	return (false);
}
int	siguienteLaberinto()
{
	return (30);
}

//		MUERTE		//
bool	esMuerte(int casilla)
{
	if (casilla == 58)
		return (true);
	return (false);
}
int	siguienteMuerte()
{
	return (1);
}

bool	esPosada(int casilla)
{
	if (casilla == 19)
		return (true);
	return (false);
}

bool	esPrision(int casilla)
{
	if (casilla == 52)
		return (true);
	return (false);
}

bool	esPozo(int casilla)
{
	if (casilla == 31)
		return (true);
	return (false);
}

bool	esMeta(int casilla)
{
	if (casilla >= 63)
		return (true);
	return (false);
}

int	efectoPosicion(int	casilla)
{
	// Determinacion del destino
	if (esPosada(casilla))
		cout << "HAS CAIDO EN LA POSADA." << endl;
	else if (esPrision(casilla))
		cout << "HAS CAIDO EN LA PRISION." << endl;
	else if (esPozo(casilla))
		cout << "HAS CAIDO EN EL POZO" << endl;
	else if (esMuerte(casilla))
	{
		cout << "MUERTE!!! VUELVES A EMPEZAR" << endl;
		return (siguienteMuerte());
	}
	else if (esLaberinto(casilla))
	{
		cout << "CAES EN EL LABERINTO" << endl;
		return(siguienteLaberinto());
	}
	else if (esPuente(casilla))
	{
		cout << "DE PUENTE A PUENTE Y TIRO PORQUE ME LLEVA LA CORRIENTE" << endl;
		return(siguientePuente(casilla));
	}
	else if (esDados(casilla))
	{
		cout << "DE DADOS A DADOS Y TIRO PORQUE ME HA TOCADO" << endl;
		return(siguienteDado(casilla));
	}
	else if (esOca(casilla))
	{
		if (!esMeta(casilla))
		{
			cout << "DE OCA A OCA Y TIRO PORQUE ME TOCA" << endl;
			return(siguienteOca(casilla));
		}
		else
		{
			cout << "HAS LLEGADO A LA META" << endl;
			return (0);
		}
	}
	return (casilla);
}

int	efectoTiradas(int casilla)
{
	if (esPosada(casilla))
		return(-1);
	else if (esPrision(casilla))
		return(-2);
	else if (esPozo(casilla))
		return(-3);
	else if (esPuente(casilla))
		return(1);
	else if (esDados(casilla))
		return(1);
	else if (esOca(casilla))
		return(1);
	return (0);	
}

int	quienEmpieza()
{
	return((rand() % 2) + 1);
}