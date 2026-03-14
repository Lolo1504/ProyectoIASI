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

/**
 * @brief Estructura que representa un nodo en el árbol de búsqueda de A*.
 */
struct NodoAStar {
    vector<vector<string>> estado;   ///< Tablero en este nodo
    int g;                            ///< Coste acumulado desde el inicio (número de movimientos)
    int h;                            ///< Valor heurístico (distancia de Z al borde)
    int f;                            ///< f = g + h (función de evaluación)
    int padre;                        ///< Índice del nodo padre en el vector `cerrados` (-1 para raíz)
    string movimiento;                ///< Letra del vehículo movido para llegar a este estado
};

/**
 * @brief Convierte un tablero en una cadena plana para usarlo como clave en búsquedas.
 * @param board Tablero 6x6.
 * @return Cadena concatenando todas las celdas.
 */
string boardToString(const vector<vector<string>> &board) {
    string s;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            s += board[i][j];
    return s;
}

/**
 * @brief Compara dos tableros para determinar si son iguales.
 * @param a Primer tablero.
 * @param b Segundo tablero.
 * @return true si son idénticos, false en caso contrario.
 */
bool boardsEqual(const vector<vector<string>> &a, const vector<vector<string>> &b) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

/**
 * @brief Reconstruye la secuencia de movimientos desde el nodo raíz hasta el nodo dado.
 * @param nodos Vector de nodos cerrados (ya expandidos).
 * @param indice Índice del nodo desde el que empezar (normalmente el padre del objetivo).
 * @return Vector con las letras de los vehículos en orden cronológico.
 */
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

/**
 * @brief Implementación del algoritmo A* para resolver el puzzle Hora Punta.
 *
 * @param estadoInicial Tablero de partida.
 * @param secuencia (salida) Vector con la secuencia de movimientos solución.
 * @param nodosGenerados (salida) Número total de nodos generados.
 * @param tiempo (salida) Tiempo de ejecución en segundos.
 * @return true si se encuentra solución, false en caso contrario.
 */
bool aStar(const vector<vector<string>> &estadoInicial,
           vector<string> &secuencia,
           int &nodosGenerados,
           double &tiempo) {
    // Inicio del cronómetro
    auto start = chrono::high_resolution_clock::now();

    vector<NodoAStar> abiertos;   // Lista de nodos frontera (por explorar)
    vector<NodoAStar> cerrados;   // Lista de nodos ya expandidos

    // Crear nodo inicial
    int hInicial = heuristic(estadoInicial);
    NodoAStar inicial;
    inicial.estado = estadoInicial;
    inicial.g = 0;
    inicial.h = hInicial;
    inicial.f = hInicial;
    inicial.padre = -1;
    inicial.movimiento = "";
    abiertos.push_back(inicial);
    nodosGenerados = 1;            // Contamos el nodo raíz

    // Bucle principal
    while (!abiertos.empty()) {
        // 1. Seleccionar el nodo de abiertos con menor f (y en caso de empate, menor h)
        int mejorIndex = 0;
        for (size_t i = 1; i < abiertos.size(); i++) {
            if (abiertos[i].f < abiertos[mejorIndex].f ||
                (abiertos[i].f == abiertos[mejorIndex].f && abiertos[i].h < abiertos[mejorIndex].h)) {
                mejorIndex = i;
            }
        }

        NodoAStar actual = abiertos[mejorIndex];
        abiertos.erase(abiertos.begin() + mejorIndex);   // Lo sacamos de abiertos

        // 2. Comprobar si es objetivo
        if (esObjetivo(actual.estado)) {
            // Reconstruir la secuencia desde el padre (que está en cerrados) y añadir el último movimiento
            secuencia = reconstruirSecuencia(cerrados, actual.padre);
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

            int gNuevo = actual.g + 1;                 // Coste acumulado hasta el sucesor
            int hNuevo = heuristic(nuevoEstado);       // Heurística del sucesor
            int fNuevo = gNuevo + hNuevo;              // f = g + h

            // 4. Comprobar si el estado ya está en cerrados con un coste g menor o igual
            bool enCerrados = false;
            for (size_t i = 0; i < cerrados.size(); i++) {
                if (boardsEqual(cerrados[i].estado, nuevoEstado)) {
                    if (cerrados[i].g <= gNuevo)
                        enCerrados = true;
                    break;
                }
            }
            if (enCerrados) continue;   // Estado ya explorado con mejor o igual camino

            // 5. Comprobar si el estado ya está en abiertos
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
                // Si el nuevo camino es mejor (menor g), actualizamos los datos del nodo en abiertos
                if (gNuevo < abiertos[indexAbierto].g) {
                    abiertos[indexAbierto].g = gNuevo;
                    abiertos[indexAbierto].f = fNuevo;
                    abiertos[indexAbierto].padre = cerrados.size(); // El padre es el nodo actual (que está a punto de añadirse a cerrados)
                    abiertos[indexAbierto].movimiento = letra;
                }
            } else {
                // No estaba ni en cerrados ni en abiertos: lo añadimos a abiertos
                NodoAStar nuevo;
                nuevo.estado = nuevoEstado;
                nuevo.g = gNuevo;
                nuevo.h = hNuevo;
                nuevo.f = fNuevo;
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
