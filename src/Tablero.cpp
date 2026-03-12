/*
 * Tablero.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Tablero.h"
#include <iostream>
using namespace std;

void impresionTablero(const vector<vector<string>> &Tablero) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << Tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void posicionX(int &x, int &y, const vector<vector<string>> &Tablero) {
    bool encontrado = false;
    for (int i = 0; i < 6 && !encontrado; i++) {
        for (int j = 0; j < 6 && !encontrado; j++) {
            if (Tablero[i][j] == "X") {
                x = i;
                y = j;
                encontrado = true;
            }
        }
    }
}

void intercambiar(int nX, int nY, string letra, vector<vector<string>> &Tablero) {
    int x, y;
    posicionX(x, y, Tablero);
    Tablero[x][y] = letra;
    Tablero[nX][nY] = "X";
}

int MovimientoAbajo(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila + 1 < 6 && Tablero[fila + 1][columna] == letra) {
        return MovimientoAbajo(Tablero, fila + 1, columna, letra);
    } else {
        return fila;
    }
}

int MovimientoArriba(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila - 1 >= 0 && Tablero[fila - 1][columna] == letra) {
        return MovimientoArriba(Tablero, fila - 1, columna, letra);
    } else {
        return fila;
    }
}

int MovimientoIzq(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna - 1 >= 0 && Tablero[fila][columna - 1] == letra) {
        return MovimientoIzq(Tablero, fila, columna - 1, letra);
    } else {
        return columna;
    }
}

int MovimientoDer(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna + 1 < 6 && Tablero[fila][columna + 1] == letra) {
        return MovimientoDer(Tablero, fila, columna + 1, letra);
    } else {
        return columna;
    }
}

bool CandidatoX(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool vertical = true;
    if ((y - 1 >= 0 && Tablero[x][y - 1] == letra) ||
        (y + 1 < 6 && Tablero[x][y + 1] == letra)) {
        vertical = false;
    }
    return vertical;
}

bool CandidatoY(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool horizontal = true;
    if ((x - 1 >= 0 && Tablero[x - 1][y] == letra) ||
        (x + 1 < 6 && Tablero[x + 1][y] == letra)) {
        horizontal = false;
    }
    return horizontal;
}


