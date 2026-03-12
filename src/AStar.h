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

bool aStar(const std::vector<std::vector<std::string>> &estadoInicial,
           std::vector<std::string> &secuencia,
           int &nodosGenerados,
           double &tiempo);

#endif
