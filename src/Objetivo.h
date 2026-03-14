/*
 * Objetivo.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef OBJETIVO_H_
#define OBJETIVO_H_

#include <string>
#include <vector>

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
bool esObjetivo(const std::vector<std::vector<std::string>> &Tablero);

#endif /* OBJETIVO_H_ */
