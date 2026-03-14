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

/**
 * @brief Implementación del algoritmo de escalada de máxima pendiente (Hill Climbing)
 *        para resolver el puzzle Hora Punta.
 *
 * El algoritmo parte del estado inicial y en cada paso evalúa todos los sucesores
 * (movimientos válidos) y selecciona aquel con mejor valor heurístico (menor h,
 * es decir, más cercano al objetivo según la heurística). Si ningún sucesor mejora
 * el valor actual, se detiene (máximo local). No utiliza memoria de estados visitados,
 * por lo que puede quedarse atascado en óptimos locales.
 *
 * @param estadoInicial Copia del tablero inicial (se pasa por copia para poder modificarlo).
 * @param secuencia Referencia donde se almacenará la secuencia de movimientos realizados.
 * @param nodosGenerados Referencia donde se devolverá el número de nodos generados (sucesores evaluados).
 * @return true si se alcanza el objetivo (Z en el borde), false en caso contrario.
 */
bool hillClimbing(vector<vector<string>> estadoInicial,
                  vector<string> &secuencia,
                  int &nodosGenerados) {
    // Estado actual comienza siendo el inicial
    vector<vector<string>> actual = estadoInicial;
    // Heurística del estado actual
    int hActual = heuristic(actual);
    // Limpiamos la secuencia de movimientos (por si contenía algo)
    secuencia.clear();
    // Contamos el nodo inicial
    nodosGenerados = 1;

    // Límite de pasos para evitar bucles infinitos (seguridad)
    int maxPasos = 1000;
    int pasos = 0;

    // Bucle principal: mientras no sea objetivo y no se supere el límite de pasos
    while (!esObjetivo(actual) && pasos < maxPasos) {
        // Generar todos los sucesores (movimientos válidos) desde el estado actual
        auto sucesores = generarMovimientos(actual);
        // Si no hay sucesores, no podemos continuar
        if (sucesores.empty()) break;

        // Buscar el sucesor con mejor (menor) heurística
        int mejorIndex = -1;
        int mejorH = INT_MAX;  // Inicializamos con el mayor valor posible
        for (size_t i = 0; i < sucesores.size(); i++) {
            // Calcular heurística del sucesor i-ésimo
            int hSucesor = heuristic(sucesores[i].second);
            nodosGenerados++;  // Cada sucesor evaluado cuenta como nodo generado
            if (hSucesor < mejorH) {
                mejorH = hSucesor;
                mejorIndex = i;
            }
        }

        // Si el mejor sucesor no mejora la heurística actual, estamos en un máximo local
        if (mejorH >= hActual) break;

        // Moverse al mejor sucesor
        actual = sucesores[mejorIndex].second;
        // Registrar el movimiento (letra del vehículo movido)
        secuencia.push_back(sucesores[mejorIndex].first);
        // Actualizar la heurística actual
        hActual = mejorH;
        pasos++;
    }

    // Devolver true si se ha alcanzado el objetivo, false en caso contrario
    return esObjetivo(actual);
}
