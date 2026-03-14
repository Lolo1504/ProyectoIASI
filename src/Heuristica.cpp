/*
 * Heuristica.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Heuristica.h"
#include <algorithm>
using namespace std;

/**
 * @brief Calcula la heurística para un estado del tablero.
 *
 * La heurística utilizada es la distancia mínima en línea recta (número de casillas)
 * desde la posición actual del coche Z hasta cualquier casilla del borde del tablero.
 * Se calcula como el mínimo de:
 *   - distancia a la fila superior:   fila de Z
 *   - distancia a la fila inferior:   5 - fila de Z
 *   - distancia a la columna izquierda: columna de Z
 *   - distancia a la columna derecha:  5 - columna de Z
 *
 * Esta heurística es admisible (nunca sobrestima) porque para mover Z hasta el borde
 * se necesitan al menos tantos movimientos como la distancia Manhattan directa,
 * y la distancia Manhattan al borde más cercano es exactamente este mínimo.
 *
 * @param Tablero Referencia constante al tablero (vector 6x6 de strings).
 * @return int Distancia mínima de Z a cualquier borde.
 */
int heuristic(const vector<vector<string>> &Tablero) {
    int zX = -1, zY = -1;  // Variables para almacenar las coordenadas de Z

    // Recorremos el tablero para localizar la posición del coche Z
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (Tablero[i][j] == "Z") {  // Encontramos Z
                zX = i;                   // Guardamos la fila
                zY = j;                   // Guardamos la columna
                break;                     // Salimos del bucle interior
            }
        }
        if (zX != -1) break;               // Si ya encontramos Z, salimos del bucle exterior
    }

    // Calculamos las distancias a los cuatro bordes
    int distArriba = zX;                   // Número de pasos hasta la fila 0
    int distAbajo  = 5 - zX;               // Número de pasos hasta la fila 5
    int distIzq    = zY;                   // Número de pasos hasta la columna 0
    int distDer    = 5 - zY;                // Número de pasos hasta la columna 5

    // Devolvemos la distancia mínima
    return min( min(distArriba, distAbajo), min(distIzq, distDer) );
}
