/*
 * Heuristica.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef HEURISTICA_H_
#define HEURISTICA_H_

#include <string>
#include <vector>

/**
 * @brief Calcula la heurística para un estado del tablero.
 *
 * La heurística utilizada es la distancia mínima (en número de movimientos)
 * desde la posición actual del coche Z hasta cualquier casilla del borde
 * del tablero (fila 0, fila 5, columna 0 o columna 5). Se asume que el coche Z
 * solo puede moverse si el hueco (X) está adyacente, pero esta heurística
 * proporciona una estimación optimista del coste restante.
 *
 * @param Tablero Referencia constante al tablero (vector 6x6 de strings).
 * @return int Distancia mínima de Z a cualquier borde: min(distArriba, distAbajo, distIzq, distDer).
 */
int heuristic(const std::vector<std::vector<std::string>> &Tablero);

#endif /* HEURISTICA_H_ */
