/*
 * AStar.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "AStar.h"
#include "Heuristica.h"
#include "Objetivo.h"
#include "Sucesores.h"
#include <chrono>
#include <climits>
using namespace std;

struct NodoAStar {
    vector<vector<string>> estado;
    int g;
    int h;
    int f;
    int padre;
    string movimiento;
};

string boardToString(const vector<vector<string>> &board) {
    string s;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            s += board[i][j];
    return s;
}

bool boardsEqual(const vector<vector<string>> &a, const vector<vector<string>> &b) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

vector<string> reconstruirSecuencia(const vector<NodoAStar> &nodos, int indice) {
    vector<string> secuencia;
    int actual = indice;
    while (actual != -1) {
        if (nodos[actual].movimiento != "")
            secuencia.insert(secuencia.begin(), nodos[actual].movimiento);
        actual = nodos[actual].padre;
    }
    return secuencia;
}

bool aStar(const vector<vector<string>> &estadoInicial,
           vector<string> &secuencia,
           int &nodosGenerados,
           double &tiempo) {
    auto start = chrono::high_resolution_clock::now();

    vector<NodoAStar> abiertos;
    vector<NodoAStar> cerrados;

    int hInicial = heuristic(estadoInicial);
    NodoAStar inicial;
    inicial.estado = estadoInicial;
    inicial.g = 0;
    inicial.h = hInicial;
    inicial.f = hInicial;
    inicial.padre = -1;
    inicial.movimiento = "";
    abiertos.push_back(inicial);
    nodosGenerados = 1;

    while (!abiertos.empty()) {
        int mejorIndex = 0;
        for (size_t i = 1; i < abiertos.size(); i++) {
            if (abiertos[i].f < abiertos[mejorIndex].f ||
                (abiertos[i].f == abiertos[mejorIndex].f && abiertos[i].h < abiertos[mejorIndex].h)) {
                mejorIndex = i;
            }
        }

        NodoAStar actual = abiertos[mejorIndex];
        abiertos.erase(abiertos.begin() + mejorIndex);

        if (esObjetivo(actual.estado)) {
            secuencia = reconstruirSecuencia(cerrados, actual.padre);
            if (actual.movimiento != "")
                secuencia.push_back(actual.movimiento);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            tiempo = elapsed.count();
            return true;
        }

        auto sucesores = generarMovimientos(actual.estado);
        for (auto &suc : sucesores) {
            string letra = suc.first;
            vector<vector<string>> nuevoEstado = suc.second;

            int gNuevo = actual.g + 1;
            int hNuevo = heuristic(nuevoEstado);
            int fNuevo = gNuevo + hNuevo;

            bool enCerrados = false;
            for (size_t i = 0; i < cerrados.size(); i++) {
                if (boardsEqual(cerrados[i].estado, nuevoEstado)) {
                    if (cerrados[i].g <= gNuevo) enCerrados = true;
                    break;
                }
            }
            if (enCerrados) continue;

            bool enAbiertos = false;
            int indexAbierto = -1;
            for (size_t i = 0; i < abiertos.size(); i++) {
                if (boardsEqual(abiertos[i].estado, nuevoEstado)) {
                    enAbiertos = true;
                    indexAbierto = i;
                    break;
                }
            }

            if (enAbiertos) {
                if (gNuevo < abiertos[indexAbierto].g) {
                    abiertos[indexAbierto].g = gNuevo;
                    abiertos[indexAbierto].f = fNuevo;
                    abiertos[indexAbierto].padre = cerrados.size();
                    abiertos[indexAbierto].movimiento = letra;
                }
            } else {
                NodoAStar nuevo;
                nuevo.estado = nuevoEstado;
                nuevo.g = gNuevo;
                nuevo.h = hNuevo;
                nuevo.f = fNuevo;
                nuevo.padre = cerrados.size();
                nuevo.movimiento = letra;
                abiertos.push_back(nuevo);
                nodosGenerados++;
            }
        }
        cerrados.push_back(actual);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    tiempo = elapsed.count();
    return false;
}


