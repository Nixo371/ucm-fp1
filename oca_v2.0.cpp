#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

const int NUM_CASILLAS = 63;

const int TURNOS_POSADA = 1;
const int TURNOS_CARCEL = 2;
const int TURNOS_POZO = 3;

const int MODO_DEBUG = true;

const int NUM_JUGADORES = 2;

typedef enum {NORMAL, OCA, PUENTE1, PUENTE2, POZO, POSADA, LABERINTO, DADO1, DADO2, CARCEL, CALAVERA} tCasilla;

typedef tCasilla tTablero[NUM_CASILLAS];

typedef int tJugadores[NUM_JUGADORES];


int tirarDado();
bool esMeta(int casilla);
int quienEmpieza();
int cambiaTurno(int turno);

bool cargaTablero(tTablero tablero);
void iniciaTablero(tTablero tablero);
tCasilla enum_func(string s);

bool esCasillaSalto(const tTablero tablero, int casilla);
void efectoTirada(const tTablero tablero, int& casillaJ, int& penalizacionJ);
int saltaACasilla(const tTablero tablero, int casillaActual);
void buscaCasillaAvanzando(const tTablero tablero, tCasilla tipo, int& posicion);
void buscaCasillaRetrocediendo(const tTablero tablero, tCasilla tipo, int& posicion);

void iniciaJugadores(tJugadores casillasJ, tJugadores penalizacionesJ);
void tirada(const tTablero tablero, int& casillaActual, int& penalizacion);
int partida(const tTablero tablero);

void pintaTablero(const tTablero tablero, const tJugadores casillasJ);
void pintaNumCasilla(int fila, int casillasPorFila);
void pintaBorde(int casillasPorFila);
void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila);
void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila);
string casillaAstring(tCasilla casilla);

int main()
{
	tTablero	tablero;
	bool		err;
	int			ganador;

	err = cargaTablero(tablero);
	if (!err)
	{
		cout << "Ha habido un error al cargar el tablero" << endl;
		return(1);
	}
	ganador = partida(tablero);
	cout << "Ha ganado el jugador " << ganador << "!!!" << endl;
    return(0);
}

void pintaTablero(const tTablero tablero, const tJugadores casillasJ) {
    int numFilas = 3;
    int casillasPorFila = NUM_CASILLAS / numFilas;
    cout << endl;
    for (int fila = 0; fila < numFilas; fila++) {
        pintaBorde(casillasPorFila);
        pintaNumCasilla(fila, casillasPorFila);
        pintaTipoCasilla(tablero, fila, casillasPorFila);
        pintaJugadores(casillasJ, fila, casillasPorFila);
    }
    pintaBorde(casillasPorFila);
    cout << endl;
}

void pintaNumCasilla(int fila, int casillasPorFila) {
    for (int i = 1; i <= casillasPorFila; i++)
        cout << "| " << setw(2) << setfill('0') << i + fila * casillasPorFila << " ";
    cout << "|" << endl;
}

void pintaBorde(int casillasPorFila) {
    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|====";
    cout << "|" << endl;
}

void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila) {
    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|" << setw(4) << setfill(' ') << casillaAstring(tablero[i - 1 + fila * casillasPorFila]);
    cout << "|" << endl;
}

void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila) {
    int casilla;
    int blancos = 4 - NUM_JUGADORES;
    string b = "";
    for (int i = 0; i < blancos; i++) b = b + " ";
    cout << "|";
    for (int i = 1; i <= casillasPorFila; i++) {
        casilla = i - 1 + fila * casillasPorFila;
        for (int jug = 0; jug < NUM_JUGADORES; jug++) {
            if (casillasJ[jug] == casilla)
                cout << jug + 1;
            else
                cout << " ";
        }
        cout << b;
        cout << "|";
    }
    cout << endl;
}

string casillaAstring(tCasilla casilla) {
    string cadena;
    switch (casilla) {
    case NORMAL:
        cadena = " ";
        break;
    case OCA:
        cadena = "OCA";
        break;
    case DADO1:
    case DADO2:
        cadena = "DADO";
        break;
    case PUENTE1:
    case PUENTE2:
        cadena = "PNTE";
        break;
    case POSADA:
        cadena = "PSDA";
        break;
    case CALAVERA:
        cadena = "MUER";
        break;
    case LABERINTO:
        cadena = "LBRN";
        break;
    case POZO:
        cadena = "POZO";
        break;
    case CARCEL:
        cadena = "CRCL";
        break;
    }
    return cadena;
}

int tirarDado()
{
	int tirada;

	if (MODO_DEBUG)
	{
		cout << "Introduzca el valor de la tirada: ";
		cin >> tirada;
	
		return (tirada);
	}
	return ((rand() % 6) + 1);
}

bool esMeta(int casilla)
{
	if (casilla >= NUM_CASILLAS)
		return (true);
	return (false);
}

int quienEmpieza()
{
	return((rand() % NUM_JUGADORES) + 1);
}

int cambiaTurno(int turno)
{
	return((turno % NUM_JUGADORES) + 1);
}

bool cargaTablero(tTablero tablero)
{
	ifstream infile;
	string	in;
	int		pos;
	string	cas;

	iniciaTablero(tablero);

	cout << "Introduzca el nombre del archivo para el tablero: ";
	cin >> in;

	infile.open("tablero");
	if (!infile.is_open())
	{
		cout << "No se ha podido abrir el archivo" << endl;
		return(false);
	}
	infile >> pos;
	infile >> cas;

	while (pos != 0)
	{
		tablero[pos - 1] = enum_func(cas);

		infile >> pos;
		infile >> cas;
	}
	return(true);
}

tCasilla enum_func(string s)
{
	tCasilla casilla;

	if (s == "OCA")
		casilla = OCA;
	else if (s == "PUENTE1")
		casilla = PUENTE1;
	else if (s == "PUENTE2")
		casilla = PUENTE2;
	else if (s == "POZO")
		casilla = POZO;
	else if (s == "POSADA")
		casilla = POSADA;
	else if (s == "LABERINTO")
		casilla = LABERINTO;
	else if (s == "DADO1")
		casilla = DADO1;
	else if (s == "DADO2")
		casilla = DADO2;
	else if (s == "CARCEL")
		casilla = CARCEL;
	else if (s == "CALAVERA")
		casilla = CALAVERA;
	else
		casilla = NORMAL;
	return(casilla);
}

void iniciaTablero(tTablero tablero)
{
	for (int i = 0; i < 62; i++)
	{
		tablero[i] = NORMAL;
	}
	tablero[62] = OCA;
}

bool esCasillaSalto(const tTablero tablero, int casilla)
{
	if (tablero[casilla - 1] == OCA)
		return(true);
	else if (tablero[casilla - 1] == PUENTE1)
		return(true);
	else if (tablero[casilla - 1] == PUENTE2)
		return(true);
	else if (tablero[casilla - 1] == DADO1)
		return(true);
	else if (tablero[casilla - 1] == DADO2)
		return(true);
	else if (tablero[casilla - 1] == LABERINTO)
		return(true);
	else if (tablero[casilla - 1] == CALAVERA)
		return(true);
	return(false);
}

void efectoTirada(const tTablero tablero, int& casillaJ, int& penalizacionJ)
{
	if (tablero[casillaJ - 1] == OCA)
		{
			cout << "De oca a oca, y tiro porque me toca!" << endl;
			buscaCasillaAvanzando(tablero, OCA, casillaJ);
		}
	else if (tablero[casillaJ - 1] == PUENTE1 || tablero[casillaJ - 1] == PUENTE2)
		{
			cout << "De puente a puente, y tiro porque me lleva la corriente!" << endl;
			casillaJ = saltaACasilla(tablero, casillaJ);
		}
	else if (tablero[casillaJ - 1] == DADO1 || tablero[casillaJ - 1] == DADO2)
		{
			cout << "De dado a dado, y tiro porque me ha tocado!" << endl;
			casillaJ = saltaACasilla(tablero, casillaJ);
		}
	
	if (tablero[casillaJ - 1] == LABERINTO)
	{
		cout << "Has caido en el laberinto!" << endl;
		casillaJ = saltaACasilla(tablero, casillaJ);
	}
	else if (tablero[casillaJ - 1] == POSADA)
	{
		cout << "Has caido en la posada, pierdes 1 turno" << endl;
		penalizacionJ -= 1;
	}
	else if (tablero[casillaJ - 1] == CARCEL)
	{
		cout << "Has caido en la carcel, pierdes 2 turnos" << endl;
		penalizacionJ -= 2;
	}
	else if (tablero[casillaJ - 1] == POZO)
	{
		cout << "Has caido en el pozo, pierdes 3 turnos" << endl;
		penalizacionJ -= 3;
	}

}

int saltaACasilla(const tTablero tablero, int casillaActual)
{
	if (tablero[casillaActual - 1] == OCA)
		buscaCasillaAvanzando(tablero, OCA, casillaActual);

	else if (tablero[casillaActual - 1] == PUENTE1)
		buscaCasillaAvanzando(tablero, PUENTE2, casillaActual);
	else if (tablero[casillaActual - 1] == PUENTE2)
		buscaCasillaRetrocediendo(tablero, PUENTE1, casillaActual);

	else if (tablero[casillaActual - 1] == DADO1)
		buscaCasillaAvanzando(tablero, DADO2, casillaActual);
	else if (tablero[casillaActual - 1] == DADO2)
		buscaCasillaRetrocediendo(tablero, DADO1, casillaActual);

	else if (tablero[casillaActual - 1] == LABERINTO)
		casillaActual -= 12;

	else if (tablero[casillaActual - 1] == CALAVERA)
		casillaActual = 1;
	return(casillaActual);
}

void buscaCasillaAvanzando(const tTablero tablero, tCasilla tipo, int& posicion)
{
	while(posicion++ <= 63)
	{
		if(tablero[posicion - 1] == tipo)
		{
			cout << "Has saltado a la casilla " << posicion << endl;
			return;
		}
	}
}

void buscaCasillaRetrocediendo(const tTablero tablero, tCasilla tipo, int& posicion)
{
	while(posicion-- >= 0)
	{
		if(tablero[posicion - 1] == tipo)
		{
			cout << "Has saltado a la casilla " << posicion << endl;
			return;
		}
	}
}

void iniciaJugadores(tJugadores casillasJ, tJugadores penalizacionesJ)
{
	int	i;

	i = 0;
	while (i < NUM_JUGADORES)
	{
		casillasJ[i] = 1;
		penalizacionesJ[i] = 1;
		i++;
	}
}

void tirada(const tTablero tablero, int& casillaActual, int& penalizacion)
{
	int	dado;

	cout << "Partimos de la casilla " << casillaActual << endl;
	dado = tirarDado();
	casillaActual += dado;
	cout << "Has sacado un " << dado << " y saltas a la casilla " << casillaActual << endl;

	if(!esMeta(casillaActual))
		efectoTirada(tablero, casillaActual, penalizacion);
}

int partida(const tTablero tablero)
{
	tJugadores	casillas;
	tJugadores	penalizaciones;
	int			jugador;

	iniciaJugadores(casillas, penalizaciones);
	jugador = quienEmpieza();
	cout << "***Empieza el jugador " << jugador << "***" << endl;

	while (1)
	{
		if (penalizaciones[jugador - 1] < 1)
		{
			cout << "Se salta el turno al jugador " << jugador << endl;
		}
		else
		{
			cout << endl << "Turno del jugador " << jugador << endl;
			do
			{
				tirada(tablero, casillas[jugador - 1], penalizaciones[jugador - 1]);
				if (esMeta(casillas[jugador - 1]))
					return(jugador);
			} while (esCasillaSalto(tablero, casillas[jugador - 1]));
		}
		jugador = (jugador % NUM_JUGADORES) + 1;
		penalizaciones[jugador - 1]++;
	}
	return(-1);
}
