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

std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>>
generarMovimientos(const std::vector<std::vector<std::string>> &Tablero);

#endif
