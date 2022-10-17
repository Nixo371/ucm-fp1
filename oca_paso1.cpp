#include <iostream>
#include <cstdlib>

using namespace std;

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


int main()
{
	int casillaJugadorConDado;
	int dado;
	int	turnos;
	char seleccion;

	srand(time(NULL));

	// Colocamos al jugador que tiene el dado en la casilla 1
	casillaJugadorConDado = 1;
	turnos = 1;
	while (turnos > 0)
	{
		cout << "Partimos de la casilla " << casillaJugadorConDado << endl;

		// Lanzamiento del dado
		/*
		do {
			cout << "Elige si quieres una tirada (A)leatoria o (M)anual: ";
			cin >> seleccion;
			if (seleccion == 'A')
				dado = tirarDadoAuto();
			else if (seleccion == 'M')
				dado = tirarDadoManual();
		} while (seleccion != 'A' || seleccion != 'M');
		*/
		dado = tirarDadoManual();
		turnos--;

		// Determinacion del destino
		casillaJugadorConDado = casillaJugadorConDado + dado;
		cout << "SALTAS A LA CASILLA " << casillaJugadorConDado << endl;
		if (esPosada(casillaJugadorConDado))
		{
			cout << "HAS CAIDO EN LA POSADA." << endl;
			turnos--;
		}
		else if (esPrision(casillaJugadorConDado))
			{
				cout << "HAS CAIDO EN LA PRISION." << endl;
				turnos -= 2;
			}
		else if (esPozo(casillaJugadorConDado))
			{
				cout << "HAS CAIDO EN EL POZO" << endl;
				turnos -= 3;
			}
		else if (esMuerte(casillaJugadorConDado))
		{
			cout << "MUERTE!!! VUELVES A EMPEZAR" << endl;
			casillaJugadorConDado = siguienteMuerte();
			cout << "HAS CAIDO EN LA MUERTE Y VUELVES A EMPEZAR. VAS A LA CASILLA: " << casillaJugadorConDado << endl;
		}
		else if (esLaberinto(casillaJugadorConDado)) 
		{
			cout << "CAES EN EL LABERINTO" << endl;
			casillaJugadorConDado = siguienteLaberinto();
			cout << "SALTAS A LA CASILLA " << casillaJugadorConDado << endl;
		}
		else if (esPuente(casillaJugadorConDado))
		{
			cout << "DE PUENTE A PUENTE Y TIRO PORQUE ME LLEVA LA CORRIENTE" << endl;
			casillaJugadorConDado = siguientePuente(casillaJugadorConDado);
			cout << "SALTAS AL PUENTE DE LA CASILLA " << casillaJugadorConDado << endl;
			turnos++;
		}
		else if (esDados(casillaJugadorConDado))
		{
			cout << "DE DADOS A DADOS Y TIRO PORQUE ME HA TOCADO" << endl;
			casillaJugadorConDado = siguienteDado(casillaJugadorConDado);
			cout << "SALTAS AL SIGUIENTE DADO EN LA CASILLA: " << casillaJugadorConDado << endl;
			turnos++;
		}
		else if (esOca(casillaJugadorConDado))
		{
			if (!esMeta(casillaJugadorConDado)) 
			{
				cout << "DE OCA A OCA Y TIRO PORQUE ME TOCA" << endl;
				casillaJugadorConDado = siguienteOca(casillaJugadorConDado);
				cout << "SALTAS A LA SIGUIENTE OCA EN LA CASILLA: " << casillaJugadorConDado << endl;
				turnos++;
			}
			else
			{
				cout << "HAS LLEGADO A LA META" << endl;
				return (0);
			}
		}
	}																									  
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


