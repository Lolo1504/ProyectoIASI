/*
 * HillClimbing.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "HillClimbing.h"
#include "Heuristica.h"
#include "Objetivo.h"
#include "Sucesores.h"
#include <climits>
using namespace std;

bool hillClimbing(vector<vector<string>> estadoInicial,
                  vector<string> &secuencia,
                  int &nodosGenerados) {
    vector<vector<string>> actual = estadoInicial;
    int hActual = heuristic(actual);
    secuencia.clear();
    nodosGenerados = 1;

    int maxPasos = 1000;
    int pasos = 0;

    while (!esObjetivo(actual) && pasos < maxPasos) {
        auto sucesores = generarMovimientos(actual);
        if (sucesores.empty()) break;

        int mejorIndex = -1;
        int mejorH = INT_MAX;
        for (size_t i = 0; i < sucesores.size(); i++) {
            int hSucesor = heuristic(sucesores[i].second);
            nodosGenerados++;
            if (hSucesor < mejorH) {
                mejorH = hSucesor;
                mejorIndex = i;
            }
        }

        if (mejorH >= hActual) break;

        actual = sucesores[mejorIndex].second;
        secuencia.push_back(sucesores[mejorIndex].first);
        hActual = mejorH;
        pasos++;
    }

    return esObjetivo(actual);
}


