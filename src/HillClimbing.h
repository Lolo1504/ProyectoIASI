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

bool hillClimbing(std::vector<std::vector<std::string>> estadoInicial,
                  std::vector<std::string> &secuencia,
                  int &nodosGenerados);

#endif
