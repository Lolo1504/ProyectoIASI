/*
 * Heuristica.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Heuristica.h"
#include <algorithm>
using namespace std;

int heuristic(const vector<vector<string>> &Tablero) {
    int zX = -1, zY = -1;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (Tablero[i][j] == "Z") {
                zX = i;
                zY = j;
                break;
            }
        }
        if (zX != -1) break;
    }
    int distArriba = zX;
    int distAbajo = 5 - zX;
    int distIzq = zY;
    int distDer = 5 - zY;
    return min(min(distArriba, distAbajo), min(distIzq, distDer));
}


