/*
 * Sucesores.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Sucesores.h"
#include "Tablero.h"
using namespace std;

vector<pair<string, vector<vector<string>>>>
generarMovimientos(const vector<vector<string>> &Tablero) {
    vector<pair<string, vector<vector<string>>>> sucesores;
    int x, y;
    posicionX(x, y, Tablero);
    string letra;

    // Abajo
    if (x + 1 < 6) {
        letra = Tablero[x + 1][y];
        if (CandidatoX(Tablero, x + 1, y, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaFila = MovimientoAbajo(copia, x + 1, y, letra);
            intercambiar(nuevaFila, y, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // Arriba
    if (x - 1 >= 0) {
        letra = Tablero[x - 1][y];
        if (CandidatoX(Tablero, x - 1, y, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaFila = MovimientoArriba(copia, x - 1, y, letra);
            intercambiar(nuevaFila, y, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // Izquierda
    if (y - 1 >= 0) {
        letra = Tablero[x][y - 1];
        if (CandidatoY(Tablero, x, y - 1, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaCol = MovimientoIzq(copia, x, y - 1, letra);
            intercambiar(x, nuevaCol, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // Derecha
    if (y + 1 < 6) {
        letra = Tablero[x][y + 1];
        if (CandidatoY(Tablero, x, y + 1, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaCol = MovimientoDer(copia, x, y + 1, letra);
            intercambiar(x, nuevaCol, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    return sucesores;
}


