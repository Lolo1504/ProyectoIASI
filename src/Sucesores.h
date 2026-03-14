/*
 * Sucesores.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef SUCESORES_H_
#define SUCESORES_H_

#include <string>
#include <vector>
#include <utility>

/**
 * @brief Genera todos los movimientos válidos (sucesores) desde un estado dado del tablero.
 *
 * Dado un tablero, localiza la posición del hueco (representado por "X") y examina
 * las cuatro casillas adyacentes (arriba, abajo, izquierda, derecha). Para cada
 * vehículo adyacente, comprueba si puede moverse hacia el hueco según las reglas:
 * - Los vehículos tienen orientación fija (horizontal o vertical) determinada por
 *   si tienen casillas del mismo tipo a izquierda/derecha (horizontal) o arriba/abajo (vertical).
 * - Un vehículo solo puede moverse si su orientación es perpendicular a la dirección
 *   del movimiento? En realidad, la lógica implementada en `CandidatoX` y `CandidatoY`
 *   verifica que el movimiento sea en la dirección de su orientación (es decir, un vehículo
 *   vertical solo puede moverse arriba/abajo, y uno horizontal solo izquierda/derecha).
 *   Las funciones `MovimientoAbajo`, `MovimientoArriba`, etc., determinan hasta dónde
 *   se desplaza el vehículo (puede moverse varias casillas si es un camión/furgoneta)
 *   hasta llenar el hueco o encontrar un obstáculo.
 *
 * Para cada movimiento válido, se genera una copia del tablero, se aplica el movimiento
 * (desplazando todo el vehículo a la posición del hueco) y se guarda un par que contiene
 * la letra del vehículo movido y el nuevo tablero resultante.
 *
 * @param Tablero Referencia constante al tablero actual (vector 6x6 de strings).
 * @return std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>>
 *         Vector de pares, donde cada par contiene:
 *         - first: letra del vehículo que se ha movido (std::string).
 *         - second: nuevo tablero después de aplicar el movimiento.
 */
std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>>
generarMovimientos(const std::vector<std::vector<std::string>> &Tablero);

#endif /* SUCESORES_H_ */
