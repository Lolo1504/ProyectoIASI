/*
 * Tablero.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include <string>
#include <vector>

/**
 * @brief Muestra por consola el contenido del tablero.
 *
 * Imprime las 6 filas y 6 columnas del tablero, separando cada celda con un espacio.
 * Útil para depuración y para mostrar el estado inicial o intermedio.
 *
 * @param Tablero Referencia constante al tablero (vector 6x6 de strings).
 */
void impresionTablero(const std::vector<std::vector<std::string>> &Tablero);

/**
 * @brief Localiza la posición del hueco (representado por "X") en el tablero.
 *
 * Recorre el tablero hasta encontrar la celda que contiene "X" y devuelve sus
 * coordenadas a través de los parámetros por referencia. Se asume que siempre
 * hay un único hueco.
 *
 * @param x Referencia a entero donde se almacenará la fila del hueco.
 * @param y Referencia a entero donde se almacenará la columna del hueco.
 * @param Tablero Referencia constante al tablero.
 */
void posicionX(int &x, int &y, const std::vector<std::vector<std::string>> &Tablero);

/**
 * @brief Intercambia el hueco con un vehículo, efectuando un movimiento.
 *
 * Dada la nueva posición del hueco (nX, nY) y la letra del vehículo que se mueve,
 * coloca "X" en (nX, nY) y la letra del vehículo en la posición anterior del hueco.
 * Es decir, realiza el movimiento completo de un vehículo hacia el hueco.
 *
 * @param nX Fila donde se colocará el hueco (nueva posición de X).
 * @param nY Columna donde se colocará el hueco.
 * @param letra Letra del vehículo que se está moviendo.
 * @param Tablero Referencia al tablero que será modificado.
 */
void intercambiar(int nX, int nY, std::string letra, std::vector<std::vector<std::string>> &Tablero);

/**
 * @brief Calcula la fila más abajo a la que puede desplazarse un vehículo vertical
 *        cuando se mueve hacia abajo (hacia el hueco).
 *
 * Parte de la posición (fila, columna) de una casilla del vehículo y desciende
 * mientras encuentre casillas del mismo vehículo. Devuelve la fila de la última
 * casilla de ese vehículo en dirección abajo.
 *
 * @param Tablero Referencia constante al tablero.
 * @param fila Fila inicial (donde se encuentra el vehículo adyacente al hueco).
 * @param columna Columna del vehículo.
 * @param letra Letra del vehículo.
 * @return int Fila de la última casilla del vehículo en dirección abajo.
 */
int MovimientoAbajo(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);

/**
 * @brief Calcula la fila más arriba a la que puede desplazarse un vehículo vertical
 *        cuando se mueve hacia arriba.
 *
 * Análogo a MovimientoAbajo, pero hacia arriba.
 *
 * @param Tablero Referencia constante al tablero.
 * @param fila Fila inicial.
 * @param columna Columna del vehículo.
 * @param letra Letra del vehículo.
 * @return int Fila de la última casilla del vehículo en dirección arriba.
 */
int MovimientoArriba(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);

/**
 * @brief Calcula la columna más a la izquierda a la que puede desplazarse un vehículo
 *        horizontal cuando se mueve hacia la izquierda.
 *
 * Parte de la posición (fila, columna) de una casilla del vehículo y se desplaza
 * a la izquierda mientras encuentre casillas del mismo vehículo. Devuelve la columna
 * de la última casilla en dirección izquierda.
 *
 * @param Tablero Referencia constante al tablero.
 * @param fila Fila del vehículo.
 * @param columna Columna inicial.
 * @param letra Letra del vehículo.
 * @return int Columna de la última casilla del vehículo en dirección izquierda.
 */
int MovimientoIzq(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);

/**
 * @brief Calcula la columna más a la derecha a la que puede desplazarse un vehículo
 *        horizontal cuando se mueve hacia la derecha.
 *
 * Análogo a MovimientoIzq, pero hacia la derecha.
 *
 * @param Tablero Referencia constante al tablero.
 * @param fila Fila del vehículo.
 * @param columna Columna inicial.
 * @param letra Letra del vehículo.
 * @return int Columna de la última casilla del vehículo en dirección derecha.
 */
int MovimientoDer(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);

/**
 * @brief Determina si un vehículo tiene orientación vertical.
 *
 * Un vehículo se considera vertical si tiene casillas del mismo tipo arriba o abajo
 * (adyacentes en la misma columna) y no tiene casillas a izquierda o derecha.
 * Esta función se usa para validar que el movimiento propuesto es coherente con la
 * orientación del vehículo.
 *
 * @param Tablero Referencia constante al tablero.
 * @param x Fila de la casilla del vehículo.
 * @param y Columna de la casilla del vehículo.
 * @param letra Letra del vehículo.
 * @return true si el vehículo es vertical, false en caso contrario (horizontal).
 */
bool CandidatoX(const std::vector<std::vector<std::string>> &Tablero, int x, int y, std::string letra);

/**
 * @brief Determina si un vehículo tiene orientación horizontal.
 *
 * Un vehículo se considera horizontal si tiene casillas del mismo tipo a izquierda o derecha
 * (adyacentes en la misma fila) y no tiene casillas arriba o abajo.
 *
 * @param Tablero Referencia constante al tablero.
 * @param x Fila de la casilla del vehículo.
 * @param y Columna de la casilla del vehículo.
 * @param letra Letra del vehículo.
 * @return true si el vehículo es horizontal, false en caso contrario (vertical).
 */
bool CandidatoY(const std::vector<std::vector<std::string>> &Tablero, int x, int y, std::string letra);

#endif /* TABLERO_H_ */
