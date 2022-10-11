#include <iostream>

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


int main()
{
	int	casillaJugadorConDado;
	int	dado;
}

int	tirarDadoManual()
{
	int	tirada;

	cout << "Introduzca el valor de la tirada: ";
	cin >> tirada;
	
	return (tirada);
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


