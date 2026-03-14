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

/**
 * @brief Estructura que representa un nodo en la búsqueda Primero el Mejor (Best‑First).
 *
 * A diferencia de A*, aquí solo almacenamos la heurística h, no el coste acumulado g.
 */
struct NodoBest {
    vector<vector<string>> estado;   ///< Tablero en este nodo
    int h;                            ///< Valor heurístico (distancia de Z al borde)
    int padre;                         ///< Índice del nodo padre en la lista `cerrados` (-1 para raíz)
    string movimiento;                 ///< Letra del vehículo movido para llegar a este estado
};

/**
 * @brief Compara dos tableros para determinar si son iguales.
 * @param a Primer tablero.
 * @param b Segundo tablero.
 * @return true si son idénticos, false en caso contrario.
 */
bool iguales(const vector<vector<string>> &a, const vector<vector<string>> &b) {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

/**
 * @brief Reconstruye la secuencia de movimientos desde el nodo raíz hasta el nodo dado.
 * @param cerrados Vector de nodos cerrados (ya expandidos).
 * @param indice Índice del nodo desde el que empezar (normalmente el padre del objetivo).
 * @return Vector con las letras de los vehículos en orden cronológico.
 */
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

/**
 * @brief Implementación del algoritmo de búsqueda Primero el Mejor (Best‑First Search)
 *        para resolver el puzzle Hora Punta.
 *
 * Best‑First es una búsqueda informada que siempre expande el nodo con menor valor
 * heurístico h (más prometedor según la heurística). No utiliza el coste acumulado,
 * por lo que puede encontrar soluciones rápidamente pero no garantiza optimalidad.
 *
 * @param estadoInicial Tablero de partida.
 * @param secuencia (salida) Vector con la secuencia de movimientos solución.
 * @param nodosGenerados (salida) Número total de nodos generados.
 * @param tiempo (salida) Tiempo de ejecución en segundos.
 * @return true si se encuentra solución, false en caso contrario.
 */
bool bestFirst(const vector<vector<string>> &estadoInicial,
               vector<string> &secuencia,
               int &nodosGenerados,
               double &tiempo) {
    // Inicio del cronómetro
    auto start = chrono::high_resolution_clock::now();

    vector<NodoBest> abiertos;   // Lista de nodos frontera (por explorar)
    vector<NodoBest> cerrados;   // Lista de nodos ya expandidos

    // Crear nodo inicial
    NodoBest inicial;
    inicial.estado = estadoInicial;
    inicial.h = heuristic(estadoInicial);
    inicial.padre = -1;
    inicial.movimiento = "";
    abiertos.push_back(inicial);
    nodosGenerados = 1;           // Contamos el nodo raíz

    // Bucle principal
    while (!abiertos.empty()) {
        // 1. Seleccionar el nodo de abiertos con menor valor heurístico h
        int mejorIndex = 0;
        for (size_t i = 1; i < abiertos.size(); ++i) {
            if (abiertos[i].h < abiertos[mejorIndex].h)
                mejorIndex = i;
        }

        NodoBest actual = abiertos[mejorIndex];
        abiertos.erase(abiertos.begin() + mejorIndex);   // Lo sacamos de abiertos

        // 2. Comprobar si es objetivo
        if (esObjetivo(actual.estado)) {
            // Reconstruir la secuencia desde el padre (que está en cerrados) y añadir el último movimiento
            secuencia = reconstruirSecuenciaBest(cerrados, actual.padre);
            if (actual.movimiento != "")
                secuencia.push_back(actual.movimiento);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            tiempo = elapsed.count();
            return true;
        }

        // 3. Generar todos los sucesores del nodo actual
        auto sucesores = generarMovimientos(actual.estado);
        for (auto &suc : sucesores) {
            string letra = suc.first;
            vector<vector<string>> nuevoEstado = suc.second;
            int hNuevo = heuristic(nuevoEstado);   // Heurística del sucesor

            // 4. Evitar ciclos: si el estado ya está en cerrados, lo ignoramos
            bool repetido = false;
            for (const auto &n : cerrados) {
                if (iguales(n.estado, nuevoEstado)) {
                    repetido = true;
                    break;
                }
            }
            if (repetido) continue;

            // 5. Comprobar si el estado ya está en abiertos
            bool enAbiertos = false;
            for (auto &n : abiertos) {
                if (iguales(n.estado, nuevoEstado)) {
                    enAbiertos = true;
                    // Nota: En Best‑First puro no se suele actualizar, porque no hay coste g.
                    // Si quisiéramos asegurar la mejor h, podríamos actualizar si el nuevo h es menor,
                    // pero para simplificar se mantiene el primero encontrado.
                    break;
                }
            }

            if (!enAbiertos) {
                // No estaba en ninguna lista: lo añadimos a abiertos
                NodoBest nuevo;
                nuevo.estado = nuevoEstado;
                nuevo.h = hNuevo;
                nuevo.padre = cerrados.size();   // El padre será el nodo actual (cuando lo metamos en cerrados)
                nuevo.movimiento = letra;
                abiertos.push_back(nuevo);
                nodosGenerados++;                 // Incrementamos el contador de nodos generados
            }
        }

        // 6. Añadimos el nodo actual a la lista de cerrados (ya expandido)
        cerrados.push_back(actual);
    }

    // Si se agota la búsqueda sin encontrar solución
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    tiempo = elapsed.count();
    return false;
}
