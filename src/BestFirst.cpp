/*
 * BestFirst.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "BestFirst.h"
#include "Heuristica.h"
#include "Objetivo.h"
#include "Sucesores.h"
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

struct NodoBest {
    vector<vector<string>> estado;
    int h;                 // solo heurística, no hay g
    int padre;             // índice del padre en la lista de cerrados
    string movimiento;
};

// Compara si dos tableros son iguales
bool iguales(const vector<vector<string>> &a, const vector<vector<string>> &b) {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

// Reconstruye la secuencia desde el nodo índice hasta la raíz
vector<string> reconstruirSecuenciaBest(const vector<NodoBest> &cerrados, int indice) {
    vector<string> secuencia;
    int actual = indice;
    while (actual != -1) {
        if (cerrados[actual].movimiento != "")
            secuencia.insert(secuencia.begin(), cerrados[actual].movimiento);
        actual = cerrados[actual].padre;
    }
    return secuencia;
}

bool bestFirst(const vector<vector<string>> &estadoInicial,
               vector<string> &secuencia,
               int &nodosGenerados,
               double &tiempo) {
    auto start = chrono::high_resolution_clock::now();

    vector<NodoBest> abiertos;
    vector<NodoBest> cerrados;

    NodoBest inicial;
    inicial.estado = estadoInicial;
    inicial.h = heuristic(estadoInicial);
    inicial.padre = -1;
    inicial.movimiento = "";
    abiertos.push_back(inicial);
    nodosGenerados = 1;

    while (!abiertos.empty()) {
        // Encontrar el nodo en abiertos con menor h
        int mejorIndex = 0;
        for (size_t i = 1; i < abiertos.size(); ++i) {
            if (abiertos[i].h < abiertos[mejorIndex].h)
                mejorIndex = i;
        }

        NodoBest actual = abiertos[mejorIndex];
        abiertos.erase(abiertos.begin() + mejorIndex);

        if (esObjetivo(actual.estado)) {
            secuencia = reconstruirSecuenciaBest(cerrados, actual.padre);
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
            int hNuevo = heuristic(nuevoEstado);

            // Comprobar si ya está en cerrados (para evitar ciclos simples)
            bool repetido = false;
            for (const auto &n : cerrados) {
                if (iguales(n.estado, nuevoEstado)) {
                    repetido = true;
                    break;
                }
            }
            if (repetido) continue;

            // Comprobar si ya está en abiertos (y si tiene mejor h, no hacemos nada porque no mejora)
            bool enAbiertos = false;
            for (auto &n : abiertos) {
                if (iguales(n.estado, nuevoEstado)) {
                    enAbiertos = true;
                    // Si el nuevo tiene menor h, podríamos actualizar, pero como es voraz,
                    // normalmente se mantiene el primero. Para simplificar, no actualizamos.
                    break;
                }
            }
            if (!enAbiertos) {
                NodoBest nuevo;
                nuevo.estado = nuevoEstado;
                nuevo.h = hNuevo;
                nuevo.padre = cerrados.size(); // el padre es el nodo actual (que se añadirá a cerrados)
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
