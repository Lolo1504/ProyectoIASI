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

bool bestFirst(const std::vector<std::vector<std::string>> &estadoInicial,
               std::vector<std::string> &secuencia,
               int &nodosGenerados,
               double &tiempo);

#endif
