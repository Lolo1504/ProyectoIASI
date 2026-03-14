/*
 * AStar.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include <string>
#include <vector>

/**
 * @brief Implementación del algoritmo de búsqueda A* para el puzzle Hora Punta.
 *
 * A* es un algoritmo de búsqueda informada que utiliza una función de evaluación
 * f(n) = g(n) + h(n), donde:
 * - g(n) es el coste real desde el nodo inicial hasta el nodo actual (número de movimientos).
 * - h(n) es una heurística que estima el coste desde el nodo actual hasta el objetivo.
 *
 * En este problema, el objetivo es llevar el coche Z (representado por "Z") a cualquier
 * casilla del borde del tablero (fila 0, fila 5, columna 0 o columna 5).
 *
 * @param estadoInicial Referencia constante al tablero inicial (vector 6x6 de strings).
 * @param secuencia Referencia a un vector de strings donde se almacenará la secuencia
 *                  de movimientos (letras de los vehículos) que conducen a la solución,
 *                  en orden cronológico.
 * @param nodosGenerados Referencia a un entero donde se devolverá el número total de
 *                       nodos generados durante la búsqueda.
 * @param tiempo Referencia a un double donde se devolverá el tiempo de ejecución
 *               del algoritmo en segundos.
 * @return true si se encontró una solución, false en caso contrario.
 */

bool aStar(const std::vector<std::vector<std::string>> &estadoInicial,
           std::vector<std::string> &secuencia,
           int &nodosGenerados,
           double &tiempo);

#endif
