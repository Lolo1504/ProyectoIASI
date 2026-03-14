/*
 * Objetivo.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Objetivo.h"
using namespace std;

/**
 * @brief Comprueba si el estado actual del tablero es un estado objetivo.
 *
 * En el puzzle Hora Punta, el objetivo se alcanza cuando el coche Z
 * (representado por la cadena "Z") se encuentra en cualquiera de las
 * casillas del borde del tablero:
 * - Fila 0 (superior)
 * - Fila 5 (inferior)
 * - Columna 0 (izquierda)
 * - Columna 5 (derecha)
 *
 * Esta función recorre el tablero para localizar la posición de Z y
 * verifica si alguna de sus coordenadas está en el borde.
 *
 * @param Tablero Referencia constante al tablero (vector 6x6 de strings).
 * @return true si Z está en el borde (estado objetivo), false en caso contrario.
 */
bool esObjetivo(const vector<vector<string>> &Tablero) {
    // Recorremos todas las filas del tablero (0 a 5)
    for (int i = 0; i < 6; i++) {
        // Recorremos todas las columnas de la fila actual (0 a 5)
        for (int j = 0; j < 6; j++) {
            // Comprobamos si la celda actual contiene el coche Z
            if (Tablero[i][j] == "Z") {
                // Si está en el borde (fila 0, fila 5, columna 0 o columna 5)
                // devolvemos true inmediatamente
                return (i == 0 || i == 5 || j == 0 || j == 5);
            }
        }
    }
    // Si no se encontró Z (no debería ocurrir según el enunciado) o Z no está en el borde,
    // devolvemos false
    return false;
}
