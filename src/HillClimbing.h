/*
 * HillClimbing.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef HILLCLIMBING_H_
#define HILLCLIMBING_H_

#include <string>
#include <vector>

/**
 * @brief Implementación del algoritmo de escalada de máxima pendiente (Hill Climbing)
 *        para el puzzle Hora Punta.
 *
 * Hill Climbing es un algoritmo de búsqueda local que parte de un estado inicial
 * y en cada paso se mueve al estado sucesor con mejor valor heurístico (menor h).
 * Si ningún sucesor mejora el valor actual, se detiene (máximo local).
 * No utiliza memoria de estados visitados, por lo que puede caer en máximos locales
 * y no garantiza encontrar una solución aunque exista.
 *
 * En este problema, la heurística utilizada es la distancia mínima del coche Z
 * a cualquier borde del tablero. El algoritmo itera hasta alcanzar el objetivo
 * (Z en el borde) o hasta que no haya mejora.
 *
 * @param estadoInicial Copia del tablero inicial (vector 6x6 de strings).
 *                      Se pasa por copia para poder modificarlo durante la búsqueda.
 * @param secuencia Referencia a un vector de strings donde se almacenará la secuencia
 *                  de movimientos (letras de los vehículos) realizados durante la escalada,
 *                  en orden cronológico. Si no se encuentra solución, contendrá los
 *                  movimientos realizados hasta el máximo local.
 * @param nodosGenerados Referencia a un entero donde se devolverá el número total de
 *                       nodos generados (sucesores evaluados) durante la búsqueda.
 * @return true si se encontró una solución (Z en el borde), false en caso contrario
 *         (máximo local o sin sucesores).
 */
bool hillClimbing(std::vector<std::vector<std::string>> estadoInicial,
                  std::vector<std::string> &secuencia,
                  int &nodosGenerados);

#endif /* HILLCLIMBING_H_ */
