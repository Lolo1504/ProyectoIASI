/*
 * Objetivo.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "Objetivo.h"
using namespace std;

bool esObjetivo(const vector<vector<string>> &Tablero) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (Tablero[i][j] == "Z") {
                return (i == 0 || i == 5 || j == 0 || j == 5);
            }
        }
    }
    return false;
}


