/*
 * BestFirst.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef BESTFIRST_H_
#define BESTFIRST_H_

#include <string>
#include <vector>

/**
 * @brief Implementación del algoritmo de búsqueda Primero el Mejor (Best‑First Search)
 *        para el puzzle Hora Punta.
 *
 * Best‑First es un algoritmo de búsqueda informada que expande siempre el nodo con
 * el menor valor heurístico h(n). No utiliza el coste acumulado g(n), por lo que
 * es una búsqueda voraz que puede encontrar soluciones rápidamente, pero no garantiza
 * optimalidad. En este problema, la heurística empleada es la distancia mínima del
 * coche Z a cualquier borde del tablero.
 *
 * @param estadoInicial Referencia constante al tablero inicial (vector 6x6 de strings).
 * @param secuencia Referencia a un vector de strings donde se devolverá la secuencia
 *                  de movimientos (letras de los vehículos) que conducen a la solución,
 *                  en orden cronológico.
 * @param nodosGenerados Referencia a un entero donde se devolverá el número total de
 *                       nodos generados durante la búsqueda.
 * @param tiempo Referencia a un double donde se devolverá el tiempo de ejecución
 *               del algoritmo en segundos.
 * @return true si se encontró una solución, false en caso contrario.
 */
bool bestFirst(const std::vector<std::vector<std::string>> &estadoInicial,
               std::vector<std::string> &secuencia,
               int &nodosGenerados,
               double &tiempo);

#endif
