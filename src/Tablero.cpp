/*
 * Tablero.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 *
 *  Este archivo implementa funciones auxiliares para la manipulación del tablero
 *  del puzzle Hora Punta. Incluye operaciones para mostrar el tablero, localizar
 *  el hueco (X), intercambiar celdas, calcular movimientos de vehículos y
 *  determinar la orientación de los vehículos.
 */

#include "Tablero.h"
#include <iostream>
using namespace std;

/**
 * @brief Muestra el tablero por consola.
 *
 * Imprime cada fila del tablero en una línea, con las celdas separadas por espacios.
 * Al final añade una línea en blanco para separar visualmente.
 *
 * @param Tablero Referencia constante al tablero 6x6.
 */
void impresionTablero(const vector<vector<string>> &Tablero) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << Tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Localiza la posición del hueco (representado por "X") en el tablero.
 *
 * Recorre el tablero hasta encontrar la primera celda que contenga "X".
 * Devuelve las coordenadas a través de los parámetros por referencia.
 * Se asume que siempre hay exactamente un hueco.
 *
 * @param x Referencia donde se almacenará la fila del hueco.
 * @param y Referencia donde se almacenará la columna del hueco.
 * @param Tablero Referencia constante al tablero.
 */
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

/**
 * @brief Intercambia el hueco (X) con la celda destino de un vehículo después de un movimiento.
 *
 * Primero localiza la posición actual del hueco mediante posicionX().
 * Luego coloca la letra del vehículo en esa posición (el hueco es ocupado por el vehículo)
 * y establece la celda destino (nX, nY) como el nuevo hueco "X".
 *
 * @param nX Fila de la nueva posición del hueco (donde estaba el extremo del vehículo).
 * @param nY Columna de la nueva posición del hueco.
 * @param letra Letra del vehículo que se está moviendo.
 * @param Tablero Referencia al tablero que será modificado.
 */
void intercambiar(int nX, int nY, string letra, vector<vector<string>> &Tablero) {
    int x, y;
    posicionX(x, y, Tablero);
    Tablero[x][y] = letra;   // El hueco pasa a ser ocupado por el vehículo
    Tablero[nX][nY] = "X";   // La celda destino se convierte en el nuevo hueco
}

/**
 * @brief Calcula la fila más lejana a la que puede desplazarse un vehículo hacia abajo.
 *
 * Función recursiva que, dada una posición inicial del vehículo (fila, columna) y su letra,
 * avanza hacia abajo mientras encuentre la misma letra. Devuelve la fila de la última
 * celda consecutiva del vehículo en esa dirección. Esto permite mover todo el vehículo
 * de una sola vez.
 *
 * @param Tablero Referencia constante al tablero actual.
 * @param fila Fila actual desde donde se comienza a buscar (posición del vehículo adyacente al hueco).
 * @param columna Columna fija (el vehículo es vertical).
 * @param letra Letra del vehículo.
 * @return int Fila de la última celda del vehículo hacia abajo.
 */
int MovimientoAbajo(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila + 1 < 6 && Tablero[fila + 1][columna] == letra) {
        return MovimientoAbajo(Tablero, fila + 1, columna, letra);
    } else {
        return fila;
    }
}

/**
 * @brief Calcula la fila más lejana a la que puede desplazarse un vehículo hacia arriba.
 *
 * Función recursiva que avanza hacia arriba mientras encuentre la misma letra.
 *
 * @param Tablero Referencia constante al tablero actual.
 * @param fila Fila actual desde donde se comienza a buscar.
 * @param columna Columna fija.
 * @param letra Letra del vehículo.
 * @return int Fila de la última celda del vehículo hacia arriba.
 */
int MovimientoArriba(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila - 1 >= 0 && Tablero[fila - 1][columna] == letra) {
        return MovimientoArriba(Tablero, fila - 1, columna, letra);
    } else {
        return fila;
    }
}

/**
 * @brief Calcula la columna más lejana a la que puede desplazarse un vehículo hacia la izquierda.
 *
 * Función recursiva que avanza hacia la izquierda mientras encuentre la misma letra.
 *
 * @param Tablero Referencia constante al tablero actual.
 * @param fila Fila fija (el vehículo es horizontal).
 * @param columna Columna actual desde donde se comienza a buscar.
 * @param letra Letra del vehículo.
 * @return int Columna de la última celda del vehículo hacia la izquierda.
 */
int MovimientoIzq(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna - 1 >= 0 && Tablero[fila][columna - 1] == letra) {
        return MovimientoIzq(Tablero, fila, columna - 1, letra);
    } else {
        return columna;
    }
}

/**
 * @brief Calcula la columna más lejana a la que puede desplazarse un vehículo hacia la derecha.
 *
 * Función recursiva que avanza hacia la derecha mientras encuentre la misma letra.
 *
 * @param Tablero Referencia constante al tablero actual.
 * @param fila Fila fija.
 * @param columna Columna actual desde donde se comienza a buscar.
 * @param letra Letra del vehículo.
 * @return int Columna de la última celda del vehículo hacia la derecha.
 */
int MovimientoDer(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna + 1 < 6 && Tablero[fila][columna + 1] == letra) {
        return MovimientoDer(Tablero, fila, columna + 1, letra);
    } else {
        return columna;
    }
}

/**
 * @brief Determina si un vehículo tiene orientación vertical (Candidato a moverse en X, es decir, vertical).
 *
 * Un vehículo es vertical si NO tiene casillas de la misma letra a izquierda o derecha.
 * La función recibe las coordenadas de una celda del vehículo y verifica si existe
 * la misma letra en las celdas adyacentes horizontales. Si existe, el vehículo es horizontal;
 * si no, es vertical.
 *
 * @param Tablero Referencia constante al tablero.
 * @param x Fila de la celda a comprobar.
 * @param y Columna de la celda a comprobar.
 * @param letra Letra del vehículo.
 * @return true si el vehículo es vertical (no tiene vecinos horizontales de la misma letra).
 * @return false si el vehículo es horizontal.
 */
bool CandidatoX(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool vertical = true;
    // Comprueba si hay la misma letra a la izquierda o derecha
    if ((y - 1 >= 0 && Tablero[x][y - 1] == letra) ||
        (y + 1 < 6 && Tablero[x][y + 1] == letra)) {
        vertical = false;   // Tiene vecinos horizontales → es horizontal
    }
    return vertical;
}

/**
 * @brief Determina si un vehículo tiene orientación horizontal (Candidato a moverse en Y, es decir, horizontal).
 *
 * Un vehículo es horizontal si NO tiene casillas de la misma letra arriba o abajo.
 * La función recibe las coordenadas de una celda del vehículo y verifica si existe
 * la misma letra en las celdas adyacentes verticales. Si existe, el vehículo es vertical;
 * si no, es horizontal.
 *
 * @param Tablero Referencia constante al tablero.
 * @param x Fila de la celda a comprobar.
 * @param y Columna de la celda a comprobar.
 * @param letra Letra del vehículo.
 * @return true si el vehículo es horizontal (no tiene vecinos verticales de la misma letra).
 * @return false si el vehículo es vertical.
 */
bool CandidatoY(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool horizontal = true;
    // Comprueba si hay la misma letra arriba o abajo
    if ((x - 1 >= 0 && Tablero[x - 1][y] == letra) ||
        (x + 1 < 6 && Tablero[x + 1][y] == letra)) {
        horizontal = false;   // Tiene vecinos verticales → es vertical
    }
    return horizontal;
}
